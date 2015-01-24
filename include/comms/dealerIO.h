#ifndef DEALERIO_H
#define DEALERIO_H

#include "dealer/player.h"
#include <stdlib.h>

bool sendBetLimits(player _player, unsigned int _min, unsigned int _max);
bool sendMoney(player _player, unsigned int _amount);
bool sendCard(player _player, PlayingCard _card);

bool receiveBet(player _player, unsigned int _timeout = 4);
bool receiveName(player _player, unsigned int _timeout = 4);

bool waitForResponse();

#endif // DEALERIO_H
