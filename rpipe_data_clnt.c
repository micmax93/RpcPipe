#include <memory.h>
#include "rpipe_data.h"

static struct timeval TIMEOUT = { 25, 0 };

u_int *
rpipe_put_1(char *data, u_int data_size,  CLIENT *clnt)
{
	rpipe_put_1_argument arg;
	static u_int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.data = data;
	arg.data_size = data_size;
	if (clnt_call (clnt, rpipe_put, (xdrproc_t) xdr_rpipe_put_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_u_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

char **
rpipe_get_1(u_int data_size,  CLIENT *clnt)
{
	static char *clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, rpipe_get,
		(xdrproc_t) xdr_u_int, (caddr_t) &data_size,
		(xdrproc_t) xdr_wrapstring, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

int *
rpipe_info_1(int info_flag,  CLIENT *clnt)
{
	static int clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, rpipe_info,
		(xdrproc_t) xdr_int, (caddr_t) &info_flag,
		(xdrproc_t) xdr_int, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
