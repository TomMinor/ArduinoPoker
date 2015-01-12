#ifndef _DECK__H_
#define _DECK__H_

#include <iostream>
#include <vector>
#include <algorithm>
#include "playingcard.h"
#include <algorithm>
#include "dealer/cardStack.h"

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
  cardStack m_pack;

};

#endif
