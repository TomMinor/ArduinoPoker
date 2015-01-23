#ifndef PACKETERRORS_H
#define PACKETERRORS_H

namespace Comms
{
    ///@brief Negative codes are errors, 0 is success
    enum PacketError {
      E_SUCCESS = 0,
      E_TIMEOUT = -1,
      E_CORRUPT = -2,
      E_DISCONNECTED = -3
    };
}

#endif // PACKETERRORS_H
