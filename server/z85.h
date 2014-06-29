#ifndef _Z85_H
#define _Z85_H

#include<stdlib.h>
typedef unsigned char byte;
extern byte *Z85_decode (char *string);
extern char* Z85_encode (byte *data, size_t size);

#endif /* !_Z85_H */
