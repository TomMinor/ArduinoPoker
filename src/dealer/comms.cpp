#include "dealer/comms.h"
#include <iostream>

comms::comms()
{

}

comms::~comms()
{

}

bool comms::sendBetLimits(player _player, unsigned int _min, unsigned int _max)
{

}

bool comms::sendCard(player _player, PlayingCard _card)
{

}

bool comms::receiveBet(player _player, unsigned int _timeout)
{

}

bool comms::receiveName(player _player, unsigned int _timeout)
{

}

void comms::waitForResponse()
{
  bool wait = true;
  int count = 0;

  while(wait)
  {
//      Sleep(10);
      count++;
      if(count > 3)
      {
        wait = false;
        fold = true;
      }
  }
}

