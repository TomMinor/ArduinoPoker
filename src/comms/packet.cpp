#include "../../include/comms/packet.h"

#include <assert.h>

namespace Comms
{

PacketError sendPacket(const Packet& _packet)
{
   uint8_t header = 0;
   uint8_t payload[_packet.payloadSize];


   // Send over serial
   //serial.write(packet);

   //return serial.sent();
   return E_SUCCESS;
}

}
