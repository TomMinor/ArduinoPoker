#include <iostream>
#include "pokerHands.h"

int main()
{
  std::vector<card> river(5);
  int numPlayers=4;
  std::vector<player> livePlayers(numPlayers);

  hands::winner(numPlayers,livePlayers,river);

  return 0;

}
