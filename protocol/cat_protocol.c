#include "cat_protocol.h"
#include <memory.h>

static void * (*pMalloc)(size_t) = malloc;
static void (*pFree)(void *) = free;

#define UINT8_T_MAX (~((uint8_t)0))
#define UINT8_T_MASK (((uint32_t)0) | ((uint32_t)(~((uint8_t)0))))

void
Cat_setMalloc(void * (*p)(size_t))
{
    if (NULL != p) {
        pMalloc = p;
    }
}

void
Cat_setFree(void (*p)(void *))
{
    if (NULL != p) {
        pFree = p;
    }
}

void
Cat_calcCheckSum(CatPacket * packet)
{
    if (NULL == packet || NULL == packet->data) {
        return;
    }
    uint32_t ret = 0;
    for (int i = 0; i < packet->length; i++) {
        ret += packet->data[i];
        // if (ret > UINT8_T_MAX - packet->data[i]) { /* 溢出情况 */
        //     ret = ret - UINT8_T_MAX;
        // }
        // else {
        //     ret += packet->data[i];
        // }
    }
    packet->checksum = ret & UINT8_T_MASK;
}

CatPacket *
Cat_createPacket(uint16_t len)
{
    CatPacket * packet = (CatPacket *)pMalloc(sizeof(CatPacket));
    if (NULL == packet) {
        return NULL;
    }
    packet->header[0] = 0x55;
    packet->header[1] = 0xFD;
    packet->header[2] = 0xAA;

    packet->length = len + 2;

    packet->common_parameter = 0x00;
    packet->spare_parameter = 0x00;
    packet->data = (uint8_t *)pMalloc(sizeof(uint8_t) * len);

    memset(packet->data, 0x00, len);

    Cat_calcCheckSum(packet);

    return packet;
}

void
Cat_setCommonParameter(CatPacket * packet,uint8_t param)
{
    if(NULL != packet){
        packet->common_parameter = param;
    }
}
    

void
Cat_setSpareParameter(CatPacket * packet, uint8_t param)
{
    if (NULL != packet) {
        packet->spare_parameter = param;
    }
}

void
Cat_setData(CatPacket * packet, uint8_t * data, uint8_t len)
{
    if (NULL != packet) {
        if (packet->length != len){
            pFree(packet->data);
            packet->length = len;
            packet->data = (uint8_t*)pMalloc(len);
        }
        memcpy(packet->data, data, len);
        Cat_calcCheckSum(packet);
    }
}
