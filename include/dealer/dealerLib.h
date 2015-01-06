#ifndef _DEALERLIB__H_
#define _DEALERLIB__H_

#include "player.h"
#include "deck.h"

class dealerLib
{
public:
  dealerLib();
  ~dealerLib();
  void Betting();
  void dealHands(deck _pack);
  void dealFlop(deck _pack);
  void dealRiverTurn(deck _pack);


  void resetCards();//player.popHole card x2 and thn set cards

private:
  std::vector<PlayingCard> m_communityCards;
  std::vector<PlayingCard>::iterator cardItr;

  std::vector<player> m_table;
};

#endif
