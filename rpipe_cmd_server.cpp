#include "rpipe_cmd.h"
#include "rpipe_data.h"
#include "data_client.hpp"
#include "z85.h"
#include "scheduler.hpp"
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
using namespace std;

#define BUFFER_SIZE 4096
Scheduler scheduler(BUFFER_SIZE);

void run_jobs()
{
    int taskType;
    while((taskType=scheduler.nextTask())!=0)
    {
        Job j = scheduler.fetchJob(taskType);
        RpipeDataClient client(j.target.host, j.target.prognum);
        if(j.type==rpipe_write)
            j.data = client.get(j.data_size);
        else if(j.type==rpipe_read)
            client.put(j.data,j.data_size);
        else
            client.info(j.type);
        scheduler.jobDone(j);
    }
}



int *
rpipe_open_1_svc(u_long cbprog_id, int flag,  struct svc_req *rqstp)
{
	static int  result;
    Descriptor d;
    d.host = string(inet_ntoa(rqstp->rq_xprt->xp_raddr.sin_addr));
    d.prognum = cbprog_id;
    d.type = flag;
	result = scheduler.openDescriptor(d);
	return &result;
}

int *
rpipe_close_1_svc(int fid,  struct svc_req *rqstp)
{
	static int  result=0;
	scheduler.closeDescriptor(fid);
	return &result;
}

int *
rpipe_write_1_svc(int fid, u_int data_size,  struct svc_req *rqstp)
{
	static int result;
	result=0;
	Task t;
	t.data_size = data_size;
	t.type = rpipe_write;
	t.desc = fid;
	try
	{
        scheduler.addTask(t);
	}
	catch(string ex)
	{
	    printf("Exception: %s\n",ex.c_str());
	    result=1;
	}
	return &result;
}

int *
rpipe_read_1_svc(int fid, u_int max_size,  struct svc_req *rqstp)
{
    printf("Read called (%i)\n",max_size);
	static int  result;
	result=0;
	Task t;
	t.data_size = max_size;
	t.type = rpipe_read;
	t.desc = fid;
	try
	{
        scheduler.addTask(t);
	}
	catch(string ex)
	{
	    printf("Exception: %s\n",ex.c_str());
	    result=1;
	}
	return &result;
}
