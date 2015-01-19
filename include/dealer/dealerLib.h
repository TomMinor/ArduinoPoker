#ifndef _DEALERLIB__H_
#define _DEALERLIB__H_

#include "player.h"
#include "deck.h"
#include "cardStack.h"

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
  void update();


  bool sendBetLimits(player _player, unsigned int _min, unsigned int _max);
  bool sendMoney(player _player, unsigned int _amount);
  bool sendCard(player _player, PlayingCard _card);
  bool sendHand(player _player, cardStack _cards);

  bool recieveBet(player _player, unsigned int &_bet, unsigned int _timeout = 4);
  bool recieveName(player _player, std::string &_name, unsigned int _timeout = 4);

private:
  cardStack m_communityCards;
  cardStack::iterator cardItr;

  std::vector<player> m_table;
};

#endif
