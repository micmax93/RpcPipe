#ifndef _Z85_UTILS_H
#define _Z85_UTILS_H

typedef unsigned char byte;
extern byte *Z85_decode (char *string);
extern char* Z85_encode (byte *data, size_t size);


#endif /* !_Z85_UTILS_H */
