#include "rpipe.h"
#include "utils.h"
#include <string>
using namespace std;

namespace RPipeServer
{
    int on_open(string name)
    {
        return 666;
    }

    int on_close(int fid)
    {
        return 666;
    }

    int on_send(int fid, char* msg)
    {
        return 666;
    }

    char* on_recv(int fid, unsigned int max_len)
    {
        char *msg = (char*)malloc(4);
        msg[0] = 'y';
        msg[1] = 'y';
        msg[2] = 'z';
        msg[3] = '\0';
        return msg;
    }
};

bool_t rpipe_open_1_svc(char *name, int *result,  struct svc_req *rqstp)
{
    bool_t retval=0;
    try {
        *result = RPipeServer::on_open(string(name));
    }
    catch(string e) {
        retval=1;
    }
    return retval;
}

bool_t rpipe_close_1_svc(int fid, int *result,  struct svc_req *rqstp)
{
    bool_t retval=0;
    try {
        *result = RPipeServer::on_close(fid);
    }
    catch(string e) {
        retval=1;
    }
    return retval;
}

bool_t rpipe_recv_1_svc(int fid, u_int max_len, char **result,  struct svc_req *rqstp)
{
    bool_t retval=0;
    try {
        *result = RPipeServer::on_recv(fid,max_len);
    }
    catch(string e) {
        retval=1;
    }
    return retval;
}

bool_t rpipe_send_1_svc(int fid, char *msg, int *result,  struct svc_req *rqstp)
{
    bool_t retval=0;
    try {
        *result = RPipeServer::on_send(fid, msg);
    }
    catch(string e) {
        retval=1;
    }
    return retval;
}

int rpipe_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
    xdr_free (xdr_result, result);
    return 1;
}
