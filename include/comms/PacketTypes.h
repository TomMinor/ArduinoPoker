#ifndef PACKETTYPES_H
#define PACKETTYPES_H

#include <assert.h>
#include <inttypes.h>

namespace Comms
{
  ///
  /// \brief The PacketType enum
  ///
    enum PacketHeader
    {                   /*  Type | Payload (Number of bytes to send/expect) */
        P_CARDS           = 0x10 | 0x01,
        P_NAME            = 0x20 | 0x0F,
        P_MONEY           = 0x30 | 0x02,
        P_LIMITS          = 0x40 | 0x04,
        P_RESETPLAYER     = 0x50 | 0x00,
        P_REQUESTBET      = 0x60 | 0x01,
        P_RECIEVEWINNINGS = 0x70 | 0x02,
        P_BETAMOUNT       = 0x80 | 0x01,
        P_RESETCARD       = 0x90 | 0x00,
    };
}


#endif // PACKETTYPES_H
