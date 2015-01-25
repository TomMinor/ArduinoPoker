#ifndef DEALERIO_H
#define DEALERIO_H

#include "dealer/player.h"
#include <stdlib.h>
#include <stdint.h>
#include <map>
#include <string>

namespace Comms
{

typedef std::map<unsigned int, std::string> PlayerDevices;

bool setPlayer(const std::string& _port, const std::vector<PlayingCard>& _cards, uint16_t _money);

bool sendBetLimits(const std::string& _port, uint16_t _min, uint16_t  _max);
bool sendMoney(const std::string& _port, uint16_t _amount);
bool sendCard(const std::string& _port, PlayingCard _card);

bool receiveBet(const std::string& _port, uint16_t &_data, unsigned int _timeout = 4);
bool receiveName(const std::string& _port, std::string &_data, unsigned int _timeout = 4);

bool waitForResponse(const std::string &_port);

}

#endif // DEALERIO_H
