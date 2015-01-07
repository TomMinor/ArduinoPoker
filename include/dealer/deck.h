#ifndef _DECK__H_
#define _DECK__H_

#include <iostream>
#include <vector>
#include "playingcard.h"
#include <algorithm>

class deck
{

public:
  deck();
  ~deck();

  void init();
  void reset();
  void shuffle();
  void printDeck();
  PlayingCard deal();

private:
  std::vector<PlayingCard> m_pack;

};

#endif
