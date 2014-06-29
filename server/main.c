#include "rpipe_cmd.h"
#include <stdio.h>

int main ()
{
	register_cmd_server();

	while(1)
	{
		printf("# Dispatcher\n");
		svc_run_once();
		printf("# Scheduler\n");
		run_jobs();
	}
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
}
