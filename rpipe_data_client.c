#include "rpipe_data.h"


void
rpipe_data_1(char *host)
{
	CLIENT *clnt;
	int  *result_1;
	char * rpipe_put_1_arg;
	char * *result_2;
	int  rpipe_get_1_arg;
	int  *result_3;
	int  rpipe_info_1_arg;

	clnt = clnt_create (host, rpipe_data, v1, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}

	result_1 = rpipe_put_1(&rpipe_put_1_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_2 = rpipe_get_1(&rpipe_get_1_arg, clnt);
	if (result_2 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_3 = rpipe_info_1(&rpipe_info_1_arg, clnt);
	if (result_3 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	clnt_destroy (clnt);
}
