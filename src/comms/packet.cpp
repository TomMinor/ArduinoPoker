#include "../../include/comms/packet.h"

#include <assert.h>
#include <string>

namespace Comms
{

PacketError sendPacket(const std::string& _port, const Packet& _packet)
{
   uint8_t header = _packet.header;
   uint8_t payload[_packet.payloadSize];



   // Send over serial
   //serial.write(packet);

   //return serial.sent();
   return E_SUCCESS;
}

}
