#ifndef _UTILS_HPP
#define _UTILS_HPP

#include <string>
#include "rpipe_data.h"

class RpipeDataClient
{
	CLIENT *clnt;
public:
    RpipeDataClient(std::string host, u_long prognum);
    ~RpipeDataClient();
    void put(u_char* data, u_int data_size);
    u_char* get(u_int data_size);
    void info(int flag);
};

#endif
