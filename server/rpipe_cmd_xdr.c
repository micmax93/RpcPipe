#include "rpipe_cmd.h"

bool_t
xdr_rpipe_open_1_argument (XDR *xdrs, rpipe_open_1_argument *objp)
{
	 if (!xdr_u_long (xdrs, &objp->cbprog_id))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->flag))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_rpipe_write_1_argument (XDR *xdrs, rpipe_write_1_argument *objp)
{
	 if (!xdr_int (xdrs, &objp->fid))
		 return FALSE;
	 if (!xdr_u_int (xdrs, &objp->data_size))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_rpipe_read_1_argument (XDR *xdrs, rpipe_read_1_argument *objp)
{
	 if (!xdr_int (xdrs, &objp->fid))
		 return FALSE;
	 if (!xdr_u_int (xdrs, &objp->max_size))
		 return FALSE;
	return TRUE;
}
