#ifndef _RPIPE_CMD_H_RPCGEN
#define _RPIPE_CMD_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


#define rpipe_cmd 0x20100160
#define v1 1

#if defined(__STDC__) || defined(__cplusplus)
#define rpipe_open_r 1
extern  int * rpipe_open_r_1(int *, CLIENT *);
extern  int * rpipe_open_r_1_svc(int *, struct svc_req *);
#define rpipe_open_w 2
extern  int * rpipe_open_w_1(int *, CLIENT *);
extern  int * rpipe_open_w_1_svc(int *, struct svc_req *);
#define rpipe_close 3
extern  int * rpipe_close_1(void *, CLIENT *);
extern  int * rpipe_close_1_svc(void *, struct svc_req *);
#define rpipe_write 4
extern  int * rpipe_write_1(int *, CLIENT *);
extern  int * rpipe_write_1_svc(int *, struct svc_req *);
#define rpipe_read 5
extern  int * rpipe_read_1(int *, CLIENT *);
extern  int * rpipe_read_1_svc(int *, struct svc_req *);
extern int rpipe_cmd_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define rpipe_open_r 1
extern  int * rpipe_open_r_1();
extern  int * rpipe_open_r_1_svc();
#define rpipe_open_w 2
extern  int * rpipe_open_w_1();
extern  int * rpipe_open_w_1_svc();
#define rpipe_close 3
extern  int * rpipe_close_1();
extern  int * rpipe_close_1_svc();
#define rpipe_write 4
extern  int * rpipe_write_1();
extern  int * rpipe_write_1_svc();
#define rpipe_read 5
extern  int * rpipe_read_1();
extern  int * rpipe_read_1_svc();
extern int rpipe_cmd_1_freeresult ();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_RPIPE_CMD_H_RPCGEN */
