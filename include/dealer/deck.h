#ifndef _DECK__H_
#define _DECK__H_

#include <vector>
#include "playingcard.h"

class deck
{

public:
  deck();
  ~deck();

  void init();
  void reset();
  void shuffle();
  PlayingCard deal();

private:
  std::vector<PlayingCard> m_cards;

};

#endif
