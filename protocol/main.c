#include "cat_protocol.h"
#include <stdio.h>

void
print_packet(CatPacket * packet)
{
    if (NULL == packet) {
        return;
    }
    uint8_t * p = packet;
    printf("packet:");

    for (int i = 0; i < 7; i++) {
        printf("%02X ", *p++);
    }

    p = packet->data;
    for (int i = 0; i < packet->length; i++) {
        printf("%02X ", *p++);
    }
    printf("%02X\n", packet->checksum);
}

int
main()
{
    CatPacket * packet = Cat_createPacket(1);
    Cat_setCommonParameter(packet, CAT_SOCKET_A);
    //Cat_setData(packet,0xCC,1);
    print_packet(packet);

    return 0;
}