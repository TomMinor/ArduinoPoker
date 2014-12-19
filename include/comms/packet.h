#ifndef __PACKET_H_
#define __PACKET_H_

#include <stdint.h>

#define FLAGMASK 0xF0
#define SIZEMASK 0x0F

enum PacketType { CARD, MONEY };

bool sendPacket(uint8_t _flag, uint8_t _size);

#endif
