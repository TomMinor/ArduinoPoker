#ifndef PACKETTYPES_H
#define PACKETTYPES_H

#include <assert.h>
#include <inttypes.h>

namespace Comms
{
    enum PacketType {
      P_CARD,
      P_BETLIMIT,
      P_BET,
      P_NAME
    };

    inline uint8_t LookupPacketTypeSize(PacketType _type)
    {
      assert((int)_type <= (int)P_NAME);

      static const uint8_t lookup[] = {
        /* P_CARD */       1,
        /* P_BETLIMIT */   2,
        /* P_BET */        1,
        /* P_NAME */       0x0F,
      };

      return lookup[_type];
    }
}


#endif // PACKETTYPES_H
