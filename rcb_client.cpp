#include "rcb.h"
#include "utils.h"

class RCbClient
{
	CLIENT *clnt;
	public:
	RCbClient(char *host)
	{
	    clnt = clnt_create (host, rcb, v1, "udp");
        if (clnt == NULL) {
            clnt_pcreateerror (host);
            exit (1);
        }
	}

	~RCbClient()
	{
	    clnt_destroy(clnt);
	}

	int call(int fid, int cbType, int retval, byte *data, size_t data_size)
	{
	    char *msg = Z85_encode(data, data_size);
        int result;
        if (rcallback_1(fid, cbType, retval, msg, &result, clnt) != RPC_SUCCESS) {
            clnt_perror (clnt, "call failed");
        }
        return result;
	}
};
