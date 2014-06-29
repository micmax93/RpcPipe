#ifndef _RPIPE_HPP
#define _RPIPE_HPP

#include "rpipe_cmd.h"
#include <string>
using namespace std;

class RPipeCmdClient
{
	CLIENT *clnt;
public:
	RPipeCmdClient(string host);
	~RPipeCmdClient();
	int open(u_long cb_id, int flag);
	int close(int fid);
	int write(int fid, size_t data_size);
	int read(int fid, size_t data_size);
};

class RPipeClient
{
    RPipeCmdClient *cmdClient;
    u_long prognum;
    SVCXPRT *transp;
    int fid;
public:
    RPipeClient(string host, string mode);
    ~RPipeClient();
    size_t rRead(u_char *data, size_t data_size);
    size_t rWrite(u_char *data, size_t data_size);
};

#endif
