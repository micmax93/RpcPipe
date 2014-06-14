#ifndef _RPIPE_DATA_H_RPCGEN
#define _RPIPE_DATA_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


#define rpipe_data 0x30100160
#define v1 1

#if defined(__STDC__) || defined(__cplusplus)
#define rpipe_put 1
extern  int * rpipe_put_1(char **, CLIENT *);
extern  int * rpipe_put_1_svc(char **, struct svc_req *);
#define rpipe_get 2
extern  char ** rpipe_get_1(int *, CLIENT *);
extern  char ** rpipe_get_1_svc(int *, struct svc_req *);
#define rpipe_info 3
extern  int * rpipe_info_1(int *, CLIENT *);
extern  int * rpipe_info_1_svc(int *, struct svc_req *);
extern int rpipe_data_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define rpipe_put 1
extern  int * rpipe_put_1();
extern  int * rpipe_put_1_svc();
#define rpipe_get 2
extern  char ** rpipe_get_1();
extern  char ** rpipe_get_1_svc();
#define rpipe_info 3
extern  int * rpipe_info_1();
extern  int * rpipe_info_1_svc();
extern int rpipe_data_1_freeresult ();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_RPIPE_DATA_H_RPCGEN */
