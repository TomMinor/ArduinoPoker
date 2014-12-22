#include <iostream>
#include "dealer/pokerHands.h"

int main()
{
  std::vector<PlayingCard> river;
  int numPlayers=4;
  std::vector<player> livePlayers(numPlayers);
  for(int i=0;i<numPlayers;i++)
  {
      livePlayers[i].setScore(1+i);
  }

  hands::winner(numPlayers,livePlayers,river);

  return 0;

}
