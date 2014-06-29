#include "rpipe_data.h"
#include "z85.h"
u_char *r_data_ptr;
size_t r_data_size;

u_int *
rpipe_put_1_svc(char *data, u_int data_size,  struct svc_req *rqstp)
{
    r_data_size = data_size;
	static u_int result;
	result=r_data_size;
    byte *buf = Z85_decode(data);
    memcpy(r_data_ptr,buf,r_data_size);
    free(buf);
	return &result;
}

char **
rpipe_get_1_svc(u_int data_size,  struct svc_req *rqstp)
{
	static char *result = NULL;
	if(result!=NULL) {free(result);}
    result = Z85_encode(r_data_ptr,r_data_size);
	return &result;
}

int *
rpipe_info_1_svc(int info_flag,  struct svc_req *rqstp)
{
	static int  result=0;
    r_data_size = 0;
	return &result;
}
