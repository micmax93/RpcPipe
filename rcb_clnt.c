/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "rcb.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

enum clnt_stat 
rcallback_1(int fid, int cbtype, int retval, char *msg, int *clnt_res,  CLIENT *clnt)
{
	rcallback_1_argument arg;
	arg.fid = fid;
	arg.cbtype = cbtype;
	arg.retval = retval;
	arg.msg = msg;
	return (clnt_call (clnt, rcallback, (xdrproc_t) xdr_rcallback_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));
}