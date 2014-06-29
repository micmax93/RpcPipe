#include "rpipe_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static u_int *
_rpipe_put_1 (rpipe_put_1_argument *argp, struct svc_req *rqstp)
{
	return (rpipe_put_1_svc(argp->data, argp->data_size, rqstp));
}

static char **
_rpipe_get_1 (u_int  *argp, struct svc_req *rqstp)
{
	return (rpipe_get_1_svc(*argp, rqstp));
}

static int *
_rpipe_info_1 (int  *argp, struct svc_req *rqstp)
{
	return (rpipe_info_1_svc(*argp, rqstp));
}

static void
rpipe_data_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		rpipe_put_1_argument rpipe_put_1_arg;
		u_int rpipe_get_1_arg;
		int rpipe_info_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case rpipe_put:
		_xdr_argument = (xdrproc_t) xdr_rpipe_put_1_argument;
		_xdr_result = (xdrproc_t) xdr_u_int;
		local = (char *(*)(char *, struct svc_req *)) _rpipe_put_1;
		break;

	case rpipe_get:
		_xdr_argument = (xdrproc_t) xdr_u_int;
		_xdr_result = (xdrproc_t) xdr_wrapstring;
		local = (char *(*)(char *, struct svc_req *)) _rpipe_get_1;
		break;

	case rpipe_info:
		_xdr_argument = (xdrproc_t) xdr_int;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) _rpipe_info_1;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

void wait_for_callback()
{
    fd_set readfds;
    while(1)
    {
        readfds = svc_fdset;
        switch (select(_rpc_dtablesize(), &readfds, (fd_set*)NULL, (fd_set*)NULL,
                       (struct timeval*)NULL))
        {
        case -1:
            if (errno == EINTR) continue;
            perror("svc_run: select failed");
            return;
        case 0:
            continue;
        default:
            svc_getreqset(&readfds);
            return;
        }
    }
}

int register_callback(SVCXPRT *transp)
{
    long prognum = rpipe_data;
    while(pmap_set(prognum, v1, IPPROTO_UDP, transp->xp_port)==0)
    {
        prognum++;
    }
    if (!svc_register(transp, prognum, v1, rpipe_data_1, IPPROTO_UDP))
    {
        fprintf (stderr, "%s", "unable to register transient procedure.");
        exit(1);
    }
    return prognum;
}

void unregister_callback(int prognum)
{
    svc_unregister(prognum, v1);
	pmap_unset (prognum, v1);
}

void _cb_run()
{
    SVCXPRT *transp = svcudp_create(RPC_ANYSOCK);
    if (transp == NULL)
    {
        fprintf (stderr, "%s", "cannot create udp service.");
        exit(1);
    }
    int prognum = register_callback(transp);
    //rpipe_open_r(prognum);
    wait_for_callback();
    unregister_callback(prognum);
    svc_destroy(transp);
}

int
_rpipe_run_data_svc (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (rpipe_data, v1);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, rpipe_data, v1, rpipe_data_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (rpipe_data, v1, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, rpipe_data, v1, rpipe_data_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (rpipe_data, v1, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
}

int
_old_svc_main_loop (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (rpipe_data, v1);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, rpipe_data, v1, rpipe_data_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (rpipe_data, v1, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, rpipe_data, v1, rpipe_data_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (rpipe_data, v1, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
}
