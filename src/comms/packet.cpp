#include "../../include/comms/packet.h"

#include <assert.h>

bool sendPacket(uint8_t _flag, uint8_t _size)
{
   uint8_t packet = 0;

   // Exit if we have overflowed the max size (15) of _size and will corrupt left hand bits during the OR operation later
   assert(_size <= 0x0F);

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
