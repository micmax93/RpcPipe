/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "rcb.h"

bool_t
xdr_rcallback_1_argument (XDR *xdrs, rcallback_1_argument *objp)
{
	 if (!xdr_int (xdrs, &objp->fid))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->cbtype))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->retval))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->msg, ~0))
		 return FALSE;
	return TRUE;
}