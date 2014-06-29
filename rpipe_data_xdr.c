#include "rpipe_data.h"

bool_t
xdr_rpipe_put_1_argument (XDR *xdrs, rpipe_put_1_argument *objp)
{
	 if (!xdr_string (xdrs, &objp->data, ~0))
		 return FALSE;
	 if (!xdr_u_int (xdrs, &objp->data_size))
		 return FALSE;
	return TRUE;
}
