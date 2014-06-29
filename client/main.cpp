#include "rpipe_client.hpp"
#include <unistd.h>
using namespace std;

int
main (int argc, char *argv[])
{
	if (argc < 3)
	{
		printf ("usage: %s server_host open_mode\n", argv[0]);
		exit (1);
	}
	string host(argv[1]);
	string mode(argv[2]);
	u_char *buffer = (u_char*)malloc(100);

	if(mode=="read")
	{
		RPipeClient clnt(host, mode);
		size_t len;
		while((len=clnt.rRead(buffer,100)))
		{
			write(1,buffer,len);
			for(int i=0;i<100;i++)
			{
				buffer[i]='\0';
			}
		}
	}
	else if(mode=="write")
	{
		RPipeClient clnt(host, mode);
		size_t len;
		while((len=read(0,buffer,100)))
		{
			clnt.rWrite(buffer,len);
		}
	}
	else
	{
		exit(1);
	}
	exit (0);
}
