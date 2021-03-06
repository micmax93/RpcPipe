#ifndef _RPIPE_CMD_H_RPCGEN
#define _RPIPE_CMD_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct rpipe_open_1_argument {
	u_long cbprog_id;
	int flag;
};
typedef struct rpipe_open_1_argument rpipe_open_1_argument;

struct rpipe_write_1_argument {
	int fid;
	u_int data_size;
};
typedef struct rpipe_write_1_argument rpipe_write_1_argument;

struct rpipe_read_1_argument {
	int fid;
	u_int max_size;
};
typedef struct rpipe_read_1_argument rpipe_read_1_argument;

#define rpipe_cmd 0x20100160
#define v1 1

#if defined(__STDC__) || defined(__cplusplus)
#define rpipe_open 1
extern  int * rpipe_open_1(u_long , int , CLIENT *);
extern  int * rpipe_open_1_svc(u_long , int , struct svc_req *);
#define rpipe_close 2
extern  int * rpipe_close_1(int , CLIENT *);
extern  int * rpipe_close_1_svc(int , struct svc_req *);
#define rpipe_write 4
extern  int * rpipe_write_1(int , u_int , CLIENT *);
extern  int * rpipe_write_1_svc(int , u_int , struct svc_req *);
#define rpipe_read 5
extern  int * rpipe_read_1(int , u_int , CLIENT *);
extern  int * rpipe_read_1_svc(int , u_int , struct svc_req *);
extern int rpipe_cmd_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define rpipe_open 1
extern  int * rpipe_open_1();
extern  int * rpipe_open_1_svc();
#define rpipe_close 2
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

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_rpipe_open_1_argument (XDR *, rpipe_open_1_argument*);
extern  bool_t xdr_rpipe_write_1_argument (XDR *, rpipe_write_1_argument*);
extern  bool_t xdr_rpipe_read_1_argument (XDR *, rpipe_read_1_argument*);

#else /* K&R C */
extern bool_t xdr_rpipe_open_1_argument ();
extern bool_t xdr_rpipe_write_1_argument ();
extern bool_t xdr_rpipe_read_1_argument ();

#endif /* K&R C */

extern void register_cmd_server();
extern void run_jobs();
extern void svc_run_once();

#ifdef __cplusplus
}
#endif

#endif /* !_RPIPE_CMD_H_RPCGEN */
