#ifndef _DECK__H_
#define _DECK__H_

#include <vector>
#include "card.h"

class deck
{

public:
  deck();
  ~deck();

  void init();
  void reset();
  void shuffle();
  card deal();

private:
  std::vector<card> m_cards;

};

#endif _DECK__H_
