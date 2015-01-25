#ifndef DEALERIO_H
#define DEALERIO_H

#include "dealer/player.h"
#include <stdlib.h>
#include <stdint.h>

namespace Comms
{

bool setPlayer(player _player, const std::vector<PlayingCard>& _cards, uint16_t _money);

bool sendBetLimits(player _player, uint16_t _min, uint16_t  _max);
bool sendMoney(player _player, uint16_t _amount);
bool sendCard(player _player, PlayingCard _card);

bool receiveBet(player _player, uint16_t &_data, unsigned int _timeout = 4);
bool receiveName(player _player, std::string &_data, unsigned int _timeout = 4);

bool waitForResponse();

}

#endif // DEALERIO_H
