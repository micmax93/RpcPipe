#include "rpipe.h"
#include "utils.h"

class RPipeClient
{
	CLIENT *clnt;
	public:
	RPipeClient(char *host)
	{
	    clnt = clnt_create (host, rpipe, v1, "udp");
        if (clnt == NULL) {
            clnt_pcreateerror (host);
            exit (1);
        }
	}

	~RPipeClient()
	{
	    clnt_destroy(clnt);
	}

	int open(char *name)
	{
        int result;
        if (rpipe_open_1(name, &result, clnt) != RPC_SUCCESS) {
            clnt_perror (clnt, "call failed");
        }
        return result;
	}

	int close(int fid)
	{
        int result;
        if (rpipe_close_1(fid, &result, clnt) != RPC_SUCCESS) {
            clnt_perror (clnt, "call failed");
        }
        return result;
	}

	int send(int fid, byte *data, size_t data_size)
	{
        int result;
        char *msg = Z85_encode(data, data_size);
        if (rpipe_send_1(fid, msg, &result, clnt) != RPC_SUCCESS) {
            clnt_perror (clnt, "call failed");
        }
        free(msg);
        return result;
	}

	byte* recv(int fid, unsigned int max_size, unsigned int &out_size)
	{
        char *msg;
        unsigned int max_len = max_size * 5 / 4;
        if (rpipe_recv_1(fid, max_len, &msg, clnt) != RPC_SUCCESS) {
            clnt_perror (clnt, "call failed");
        }
        out_size = strlen(msg) * 4 / 5;
        return Z85_decode(msg);
	}

};

//
//int main (int argc, char *argv[])
//{
//	char *host;
//
//	if (argc < 2) {
//		printf ("usage: %s server_host\n", argv[0]);
//		exit (1);
//	}
//	host = argv[1];
//	RPipeClient r(host);
//    exit (0);
//}
