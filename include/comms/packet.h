#ifndef __PACKET_H_
#define __PACKET_H_

#include <stdint.h>
#include <assert.h>

#include "PacketErrors.h"
#include "PacketTypes.h"

#define PACKET_PAYLOADTYPEMASK    (0xF0)
#define PACKET_PAYLOADLENGTHMASK  (0x0F)
#define PACKET_HEADERTYPE(x)      ((PACKET_PAYLOADTYPEMASK & x) >> 4 )
#define PACKET_HEADERLENGTH(x)    ( PACKET_PAYLOADTYPEMASK & x )

namespace Comms
{

  ///
  /// \brief  The packet protocol reads the payload length/type from the header file.
  /// [{Type}{Number of bytes}][Byte0][Byte1]..[ByteN]
struct Packet
{
  ///
  /// \brief header Left nibble contains the packet content type,
  /// the right nibble contains the payload length
  ///
  uint8_t header;

  ///
  /// \brief payload The byte values to be sent across the serial connection
  ///
  uint8_t* payload;

  ///
  /// \brief payloadSize How many bytes are to be sent across the serial connection
  ///
  uint8_t payloadSize;

  ///
  /// \brief Packet constructor initializes the payload array.
  /// \param _type The type of data to send
  /// \param _size Size of the packet payload
  ///
  Packet(PacketType _type)
  {
    payloadSize = LookupPacketTypeSize(_type);

    // Exit if we have overflowed the max size (15) payloadSize and
    // will corrupt left hand bits during the OR operation later
    assert(payloadSize <= 0x0F);

    payload = new uint8_t[payloadSize];
  }

  ///@brief Packet destructor deallocates the payload memory.
  ~Packet()
  {
    delete [] payload;
  }
};

}

#endif
