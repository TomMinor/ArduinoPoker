#ifndef _DEALERLIB__H_
#define _DEALERLIB__H_

#include <map>
#include "player.h"
#include "deck.h"
#include "cardStack.h"
#include "comms/dealerIO.h"
#include "comms/SerialPort.h"
#include "gui/gui_dealergui.h"
#include "pokerHands.h"

enum commsRequest
{
  SENDBETLIMIT,
  SENDMONEY,
  SENDCARD,
  GETNAME,
  GETBET,
  WAIT
};

class dealerLib
{
public:
  ///
  /// \brief dealerLib The constructor for the dealer which will initialise the deck
  ///
  dealerLib();
  ~dealerLib();
  ///
  /// \brief Betting
  ///
  void Betting();

  ///
  /// \brief bet implements the whole betting loop
  ///
  void bet();

  ///
  /// \brief checkBoolArray
  /// \param _array
  /// \return
  ///
  bool checkBoolArray(bool _array[])const;

  ///
  /// \brief addBetToPot
  /// \param _bet This is the amount the player has bet
  ///
  void addBetToPot(const int &_bet);

  ///
  /// \brief dealHands Appends a card to each player's vector of hole cards
  ///
  void dealHands();

  ///
  /// \brief dealFlop Adds the first three cards to the vector of community cards
  ///
  void dealFlop();

  ///
  /// \brief dealRiverTurn Adds the 4th and 5th cards to the vector of community cards
  ///
  void dealRiverTurn();

  ///
  /// \brief checkMaxBet The maximum bet is the smallest amount of money a player has.
  /// The function iterates through all the live players and works out who has the least money
  /// by setiing the maxBet if its the smallest amount so far
  /// \return int maxBet
  ///
  int checkMaxBet();

  ///
  /// \brief resetCards removes all cards from
  ///
  void reset();

  ///
  /// \brief update
  ///
  void update();

  ///
  /// \brief init
  ///
  void init();

  ///
  /// \brief initPlayer
  /// \param _id
  ///
  void initPlayer(const int &_id);

  ///
  /// \brief clearTable
  ///
  void clearTable();

  ///
  /// \brief removePlayer
  /// \param it
  ///
  void removePlayer(std::vector<player>::iterator it);

  ///
  /// \brief checkIfLost
  /// \param _player
  /// \return
  ///
  bool checkIfLost(player _player);

  ///
  /// \brief kickBrokePlayer
  ///
  void kickBrokePlayer();

  ///
  /// \brief decideWinners
  ///
  void decideWinners();


  ///
  /// \brief getNumPlayers
  /// \return
  ///
  int getNumPlayers()const;

  ///
  /// \brief getLivePlayers
  /// \return
  ///
  std::vector<player> getLivePlayers()const;

  ///
  /// \brief sendWinnersToGui
  /// \param _winners
  /// \return
  ///
  std::vector<int> getWinnerIds(std::vector<player> _winners);

  ///
  /// \brief isRemainder
  /// \param _remainder
  /// \return
  ///
  bool isRemainder(int _remainder);

  void updatePlayer(int _element);

private:

  ///
  /// \brief m_communityCards
  ///
  cardStack m_communityCards;

  ///
  /// \brief cardItr
  ///
  cardStack::iterator cardItr;

  ///
  /// \brief m_numPlayers
  ///
  int m_numPlayers;

  ///
  /// \brief m_pot
  ///
  unsigned int m_pot;

  ///
  /// \brief m_deck
  ///
  deck m_deck;

  ///
  /// \brief m_dealerGui
  ///
  GUI::DealerGUI m_dealerGui;

  ///
  /// \brief m_deviceMap
  ///
  Comms::PlayerDevices m_deviceMap;

  ///
  /// \brief m_table
  ///
  std::vector<player> m_table;

  ///
  /// \brief m_livePlayers
  ///
  std::vector<player> m_livePlayers;

};

#endif

