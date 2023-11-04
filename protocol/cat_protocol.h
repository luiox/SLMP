#ifndef CAT_PROTOCOL_H
#define CAT_PROTOCOL_H

#include <stdint.h>
#include <stdlib.h>

#define CAT_SOCKET_A 0x61
#define CAT_SOCKET_B 0x62
#define CAT_SOCKET_C 0x63
#define CAT_SOCKET_D 0x64

typedef struct tagaCatPacket {
    /* 包头部固定3字节为 0x55 0xFD 0xAA */
    uint8_t header[3];
    /* 长度是指整个数据包中的有效数据的长度，
     * 从参数区（包含参数区）开始到和校验之前（不包含和校验）的所有字节数的总和，
     * 其实际数值相当于数据字节长度+2，即 n+2。 */
    uint16_t length;
    /* 常用参数区为 Socket 编码，采用 0x61 开始的编码进行表示，
     * 若序号为 0x61，代表数据发向Socket A；若为 0x62，
     * 代表数据发向 Socket B 的连接对象，
     * 其他 Socket 编号依次类推，即
     * 0x63、0x64 代表 Socket C、Socket D。 */
    uint8_t common_parameter;
    /* MCU 向模块发送套接字分发协议时备用参数区默认为 0x00。 */
    uint8_t spare_parameter;
    /*  用户数据放置区域，长度可变，最大不超过设备允许的最大数据缓存 */
    uint8_t * data;
    /* CheckSum校验和，从参数区（包含参数区）开始算起，到校验字节之前，加和取最后一个字节作为校验字节。
     */
    uint8_t checksum;
} CatPacket;

void Cat_setMalloc(void * (*p)(size_t));
void Cat_setFree(void (*p)(void *));
CatPacket * Cat_createPacket(uint16_t len);
void Cat_setCommonParameter(CatPacket * packet, uint8_t param);
void Cat_setSpareParameter(CatPacket * packet, uint8_t param);
void Cat_setData(CatPacket * packet, uint8_t* data,uint8_t len);

#endif /* CAT_PROTOCOL_H */
