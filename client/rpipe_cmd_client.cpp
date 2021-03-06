#include "rpipe_client.hpp"
#include "rpipe_cmd.h"
#include "rpipe_data.h"
#include "z85.h"
#include <unistd.h>
#include <string>
using namespace std;

RPipeCmdClient::RPipeCmdClient(string host)
{
	clnt = clnt_create (host.c_str(), rpipe_cmd, v1, "udp");
	if (clnt == NULL)
	{
	    clnt_pcreateerror (host.c_str());
	    exit (1);
	}
}

RPipeCmdClient::~RPipeCmdClient()
{
	clnt_destroy (clnt);
}

int RPipeCmdClient::open(u_long cb_id, int flag)
{
	int *result_1 = rpipe_open_1(cb_id, flag, clnt);
	if (result_1 == (int *) NULL) {
	    clnt_perror (clnt, "call failed");
	}
	return *result_1;
}

int RPipeCmdClient::close(int fid)
{
	int *result_2 = rpipe_close_1(fid, clnt);
	if (result_2 == (int *) NULL) {
	    clnt_perror (clnt, "call failed");
	}
	return *result_2;
}

int RPipeCmdClient::write(int fid, size_t data_size)
{
	int *result_3 = rpipe_write_1(fid, data_size, clnt);
	if (result_3 == (int *) NULL) {
	    clnt_perror (clnt, "call failed");
	}
	return *result_3;
}

int RPipeCmdClient::read(int fid, size_t data_size)
{
	int *result_4 = rpipe_read_1(fid, data_size, clnt);
	if (result_4 == (int *) NULL) {
	    clnt_perror (clnt, "call failed");
	}
	return *result_4;
}





RPipeClient::RPipeClient(string host, string mode)
{
	cmdClient = new RPipeCmdClient(host);

	int md;
	if(mode=="read") md=rpipe_read;
	else if(mode=="write") md=rpipe_write;
	else throw "Invalid mode.";

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL)
	{
	    fprintf (stderr, "%s", "cannot create udp service.");
	    exit(1);
	}
	prognum = register_callback(transp);

	fid = cmdClient->open(prognum, md);
	wait_for_callback();
}

RPipeClient::~RPipeClient()
{
	cmdClient->close(fid);
	delete cmdClient;
	unregister_callback(prognum);
	svc_destroy(transp);
}

size_t RPipeClient::rRead(u_char *data, size_t data_size)
{
	r_data_ptr = data;
	r_data_size = data_size;
	int status = cmdClient->read(fid, data_size);
	if(status)
	{
	    printf("Failed with status %i\n",status);
	    exit(status);
	}
	wait_for_callback();
	return r_data_size;
}

size_t RPipeClient::rWrite(u_char *data, size_t data_size)
{
	r_data_ptr = data;
	r_data_size = data_size;
	int status = cmdClient->write(fid, data_size);
	if(status)
	{
	    printf("Failed with status %i\n",status);
	    exit(status);
	}
	wait_for_callback();
	return r_data_size;
}


