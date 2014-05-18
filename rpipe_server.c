/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "rpipe.h"
#include "protocol.h"

int *
open_1_svc(char **argp, struct svc_req *rqstp)
{
	static int  result;

	struct packet_t pck = str2packet(*argp);
	printf("%i: %s\n",pck.fid,pck.msg_data);
	free_packet(pck);
	/*
	 * insert server code here
	 */

	return &result;
}

int *
close_1_svc(int *argp, struct svc_req *rqstp)
{
	static int  result;

	/*
	 * insert server code here
	 */

	return &result;
}

char **
recv_1_svc(int *argp, struct svc_req *rqstp)
{
	static char * result;

	/*
	 * insert server code here
	 */

	return &result;
}

int *
send_1_svc(char **argp, struct svc_req *rqstp)
{
	static int  result;

	/*
	 * insert server code here
	 */

	return &result;
}
