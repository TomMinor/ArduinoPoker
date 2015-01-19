#include "../../include/comms/packet.h"

#include <assert.h>

bool sendPacket(const Packet& _packet)
{
   uint8_t packet = 0;



   // Combine packet
   packet |= (FLAGMASK & (_flag << 4));
   packet |= (SIZEMASK & _size);

   // Send over serial
   //serial.write(packet);

   //return serial.sent();
   return true;
}

//switch(packetType)
//{
//   case CARD:   { sendPacket(CARD, 1);  break; }
//   case MONEY:  { sendPacket(MONEY, 2); break; }
//}
