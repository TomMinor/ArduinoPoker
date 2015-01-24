#ifndef _DEALERLIB__H_
#define _DEALERLIB__H_

#include "player.h"
#include "deck.h"
#include "cardStack.h"
#include "comms.h"

class dealerLib
{
public:
  dealerLib();
  ~dealerLib();
  void Betting();
  void dealHands(deck _pack);
  void dealFlop(deck _pack);
  void dealRiverTurn(deck _pack);
  void resetCards();
  void update();
  int checkMaxBet();
  void initialisePlayers();
  void clearTable();
  void removePlayer(std::vector<player>::iterator it);
  bool checkIfLost(player _player);
  void removeTheNoobs();
//  void addBetsToPot(); probs dont need this anymore, just hardcoded it into Betting()


private:
  cardStack m_communityCards;
  cardStack::iterator cardItr;
  int m_numPlayers;
  int m_pot;

  std::vector<player> m_table;
  std::vector<player> m_livePlayers;
};

#endif

