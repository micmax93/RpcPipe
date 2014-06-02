#include "rcb.h"
#include "utils.h"
#include <string>
using namespace std;

namespace RCbServer
{
    int on_callback(int fid, int cbtype, int retval, byte *data)
    {
        return 666;
    }
};


bool_t
rcallback_1_svc(int fid, int cbtype, int retval, char *msg, int *result,  struct svc_req *rqstp)
{
	bool_t retcode=0;
    try {
        byte *data = Z85_decode(msg);
        *result = RCbServer::on_callback(fid, cbtype, retval, data);
    }
    catch(string e) {
        retcode=1;
    }
    return retcode;
}

int
rcb_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
	xdr_free (xdr_result, result);
	return 1;
}
