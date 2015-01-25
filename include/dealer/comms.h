#ifndef COMMS_H
#define COMMS_H

#include "dealer/player.h"
#include <stdlib.h>

class comms
{
  public:
    comms();
    ~comms();

    bool sendBetLimits(player _player, unsigned int _min, unsigned int _max);
    bool sendMoney(player _player, unsigned int _amount);
    bool sendCard(player _player, PlayingCard _card);

    bool receiveBet(player _player, uint16_t& _betvalue, unsigned int _timeout = 4);
    bool receiveName(player _player, std::string& _name, unsigned int _timeout = 4);

    void waitForResponse();

};


#endif // COMMS_H
