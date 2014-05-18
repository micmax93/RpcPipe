#include<stdlib.h>
#include "z85.c"


struct packet_t {
    int fid;
    size_t mgs_size;
    unsigned char *msg_data;
};

char *packet2str(struct packet_t packet) {
    size_t prefix = sizeof(packet.fid);
    size_t total = packet.mgs_size + prefix;

    byte *buff = malloc(total);
    memcpy(buff, &packet.fid, prefix);
    memcpy(buff+prefix, packet.msg_data, packet.mgs_size);

    char *strpck = Z85_encode(buff, total);
    free(buff);
    return strpck;
}

struct packet_t str2packet(char *strpck) {
    struct packet_t packet;
    size_t prefix = sizeof(packet.fid);

    byte *buffer = Z85_decode(strpck);

    packet.mgs_size = strlen (strpck) * 4 / 5;
    packet.fid = *((int*)buffer);
    packet.msg_data = buffer + prefix;

    return packet;
}


void free_packet(struct packet_t packet) {
    byte *buffer = packet.msg_data - sizeof(packet.fid);
    free(buffer);
}

