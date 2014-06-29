#include <memory.h>
#include "rpipe_cmd.h"

static struct timeval TIMEOUT = { 25, 0 };

int *
rpipe_open_1(u_long cbprog_id, int flag,  CLIENT *clnt)
{
	rpipe_open_1_argument arg;
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.cbprog_id = cbprog_id;
	arg.flag = flag;
	if (clnt_call (clnt, rpipe_open, (xdrproc_t) xdr_rpipe_open_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

int *
rpipe_close_1(int fid,  CLIENT *clnt)
{
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, rpipe_close,
		(xdrproc_t) xdr_int, (caddr_t) &fid,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

int *
rpipe_write_1(int fid, u_int data_size,  CLIENT *clnt)
{
	rpipe_write_1_argument arg;
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.fid = fid;
	arg.data_size = data_size;
	if (clnt_call (clnt, rpipe_write, (xdrproc_t) xdr_rpipe_write_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

int *
rpipe_read_1(int fid, u_int max_size,  CLIENT *clnt)
{
	rpipe_read_1_argument arg;
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.fid = fid;
	arg.max_size = max_size;
	if (clnt_call (clnt, rpipe_read, (xdrproc_t) xdr_rpipe_read_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
