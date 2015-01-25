#ifndef _DEALERLIB__H_
#define _DEALERLIB__H_

#include "player.h"
#include "deck.h"
#include "cardStack.h"
#include "comms.h"
#include "gui/gui_dealergui.h"

enum commsRequest
{
  sendBetLimits,
  sendMoney,
  sendCard,
  getName,
  getBet,
  wait
};

class dealerLib
{
public:
  dealerLib();
  ~dealerLib();
  void Betting();
  void bet();
  bool checkBoolArray(bool _array[])const;
  void addBetToPot(const int &_bet);
  int checkMaxBet();
  void dealHands(deck _pack);
  void dealFlop(deck _pack);
  void dealRiverTurn(deck _pack);
  void resetCards();
  void update();
  void init();
  void initPlayer(const int &_id);
  void clearTable();
  void removePlayer(std::vector<player>::iterator it);
  bool checkIfLost(player _player);
  void removeTheNoobs();


  bool callComms(commsRequest request);
  int getNumPlayers()const;
  std::vector<player> getLivePlayers()const;


private:
  cardStack m_communityCards;
  cardStack::iterator cardItr;
  int m_numPlayers;

  unsigned int m_pot;
  deck m_deck;
  GUI::DealerGUI dealerGui;


  std::vector<player> m_table;
  std::vector<player> m_livePlayers;
};

#endif

