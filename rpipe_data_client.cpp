#include "data_client.hpp"
#include "rpipe_data.h"
#include "z85.c"
#include<string>
using namespace std;

RpipeDataClient::RpipeDataClient(string host, u_long prognum)
{
    clnt = clnt_create (host.c_str(), prognum, v1, "udp");
    if (clnt == NULL)
    {
        clnt_pcreateerror (host.c_str());
        exit (1);
    }
    printf("Created client to %s %lu\n",host.c_str(),prognum);
}

RpipeDataClient::~RpipeDataClient()
{
    clnt_destroy (clnt);
}

void RpipeDataClient::put(byte* data, u_int data_size)
{
    printf("Calling put (%i)\n", data_size);
    char *msg = Z85_encode(data, data_size);
    u_int *result = rpipe_put_1(msg, data_size, clnt);
    if (result == (u_int *) NULL)
    {
        clnt_perror (clnt, "Call failed\n");
        throw "call failed";
    }
}

byte* RpipeDataClient::get(u_int data_size)
{
    printf("Calling get...\n");
    char **result = rpipe_get_1(data_size, clnt);
    if (result == (char **) NULL)
    {
        clnt_perror (clnt, "Call failed\n");
        throw "call failed";
    }
    printf("Recieved strlen=%lu\n",strlen(*result));
    return Z85_decode(*result);
}

void RpipeDataClient::info(int flag)
{
    printf("Calling info (%i)\n", flag);
    int *result = rpipe_info_1(flag, clnt);
    if (result == (int *) NULL)
    {
        clnt_perror (clnt, "Call failed\n");
        throw "call failed";
    }
}


