#include "rpipe_cmd.h"


void
rpipe_cmd_1(char *host)
{
	CLIENT *clnt;
	int  *result_1;
	int  rpipe_open_r_1_arg;
	int  *result_2;
	int  rpipe_open_w_1_arg;
	int  *result_3;
	char *rpipe_close_1_arg;
	int  *result_4;
	int  rpipe_write_1_arg;
	int  *result_5;
	int  rpipe_read_1_arg;


	clnt = clnt_create (host, rpipe_cmd, v1, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}

	result_1 = rpipe_open_r_1(&rpipe_open_r_1_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_2 = rpipe_open_w_1(&rpipe_open_w_1_arg, clnt);
	if (result_2 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_3 = rpipe_close_1((void*)&rpipe_close_1_arg, clnt);
	if (result_3 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_4 = rpipe_write_1(&rpipe_write_1_arg, clnt);
	if (result_4 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	result_5 = rpipe_read_1(&rpipe_read_1_arg, clnt);
	if (result_5 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	clnt_destroy (clnt);
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	rpipe_cmd_1 (host);
exit (0);
}
