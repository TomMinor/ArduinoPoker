#ifndef PACKETTYPES_H
#define PACKETTYPES_H

#include <assert.h>
#include <inttypes.h>

namespace Comms
{
    enum PacketType
    {
        P_CARDS           = 0x10,
        P_NAME            = 0x20,
        P_MONEY           = 0x30,
        P_LIMITS          = 0x40,
        P_RESETPLAYER     = 0x50,
        P_REQUESTBET      = 0x60,
        P_RECIEVEWINNINGS = 0x70,
        P_BETAMOUNT       = 0x80,
        P_RESETCARD       = 0x90,
    };

    inline uint8_t LookupPacketTypeSize(PacketType _type)
    {
      assert((int)_type < 0x0F);

      static const uint8_t lookup[0x0F] = {
          /*P_CARDS*/           1,
          /*P_NAME*/            15,
          /*P_MONEY*/           2,
          /*P_LIMITS*/          4,
          /*P_ROUNDSTATE*/      1,
          /*P_REQUESTBET*/      1,
          /*P_RECIEVEWINNINGS*/ 1,
          /*P_BETAMOUNT*/       1,
      };

      return lookup[_type];
    }
}


#endif // PACKETTYPES_H
