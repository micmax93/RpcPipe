#include "rpipe_cmd.h"
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

static int *
_rpipe_open_1 (rpipe_open_1_argument *argp, struct svc_req *rqstp)
{
	return (rpipe_open_1_svc(argp->cbprog_id, argp->flag, rqstp));
}

static int *
_rpipe_close_1 (int  *argp, struct svc_req *rqstp)
{
	return (rpipe_close_1_svc(*argp, rqstp));
}

static int *
_rpipe_write_1 (rpipe_write_1_argument *argp, struct svc_req *rqstp)
{
	return (rpipe_write_1_svc(argp->fid, argp->data_size, rqstp));
}

static int *
_rpipe_read_1 (rpipe_read_1_argument *argp, struct svc_req *rqstp)
{
	return (rpipe_read_1_svc(argp->fid, argp->max_size, rqstp));
}

static void
rpipe_cmd_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		rpipe_open_1_argument rpipe_open_1_arg;
		int rpipe_close_1_arg;
		rpipe_write_1_argument rpipe_write_1_arg;
		rpipe_read_1_argument rpipe_read_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case rpipe_open:
		_xdr_argument = (xdrproc_t) xdr_rpipe_open_1_argument;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) _rpipe_open_1;
		break;

	case rpipe_close:
		_xdr_argument = (xdrproc_t) xdr_int;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) _rpipe_close_1;
		break;

	case rpipe_write:
		_xdr_argument = (xdrproc_t) xdr_rpipe_write_1_argument;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) _rpipe_write_1;
		break;

	case rpipe_read:
		_xdr_argument = (xdrproc_t) xdr_rpipe_read_1_argument;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) _rpipe_read_1;
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

void svc_run_once()
{
    fd_set readfds = svc_fdset;
    int done = FALSE;
    int fd;
    while(!done)
    {
        fd = select(_rpc_dtablesize(), &readfds, NULL, NULL, NULL);
        switch (fd)
        {
        case -1:
            if (errno == EINTR) continue;
            perror("svc_run: - select failed");
            done = TRUE;
            break;
        case 0:
            continue;
        default:
            svc_getreqset(&readfds);
            done = TRUE;
            break;
        }
    }
}


int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (rpipe_cmd, v1);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, rpipe_cmd, v1, rpipe_cmd_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (rpipe_cmd, v1, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, rpipe_cmd, v1, rpipe_cmd_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (rpipe_cmd, v1, tcp).");
		exit(1);
	}

    while(1)
    {
        printf("# Dispatcher\n");
        svc_run_once();
        printf("# Scheduler\n");
        run_jobs();
    }

	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
}
