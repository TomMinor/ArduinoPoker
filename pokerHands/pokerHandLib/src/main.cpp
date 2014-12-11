#include <iostream>
#include "pokerHands.h"

int main()
{
  std::vector<card> river(5);
  int numPlayers=4;
  std::vector<player> livePlayers(numPlayers);
  for(int i=0;i<numPlayers;i++)
  {
      livePlayers[i].setScore(4-i);
  }

  hands::winner(numPlayers,livePlayers,river);

  return 0;

}
