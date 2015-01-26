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
  /// \brief checkBoolArray checks if all elements in the array are true
  /// \param _array
  /// \return boolean This is used as the condition of a while loop.
  /// Betting ends when all elements of the array are the same (true)
  ///
  bool checkBoolArray(bool _array[])const;

  ///
  /// \brief addBetToPot adds players bet to the pot
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
  /// The function iterates through all the live players and works out who has the least money.
  /// This value is then used as the maximum allowance a player can bet
  /// \return int maxBet The maximum amount of money a player can bet
  ///
  int checkMaxBet();

  ///
  /// \brief reset Removes all cards from the game and resets the deck. It also updates player
  /// information to the m_table vector from the more temporary m_livePlayers vector and resets all
  /// the player's fold booleans to false
  ///
  void reset();

  ///
  /// \brief update Calls the guis update and draw functions
  ///
  void update();

  ///
  /// \brief init Initialises gui and player and sets up a std::map that maps
  /// the playerId to a serialPort
  ///
  void init();

  ///
  /// \brief initPlayer Initialises a vector of players, m_table, and sets the players Ids
  /// and name
  /// \param _id The position in the vector is used to set the players ID
  ///
  void initPlayer(const int &_id);


  ///
  /// \brief removePlayer removes the player from a vector. This will be called when a player runs out of money
  /// and when a player folds
  /// \param it The iterator of a vector of players
  ///
  void removePlayer(std::vector<player>::iterator it);

  ///
  /// \brief checkIfLost Checks if a player has ran out of money
  /// \param _player The player who is being checked
  /// \return boolean If the player has no money, its set to true
  ///
  bool checkIfLost(player _player);

  ///
  /// \brief kickBrokePlayer Removes a player that has ran out of money. Its used after calling
  /// the checkIfLost() function
  ///
  void kickBrokePlayer();

  ///
  /// \brief decideWinners Calculates which players have won and creates a vector of winners
  /// It also passes the money in the pot to these winners. If there is more than one winner,
  /// the pot is split. If it can't be split evenly,the remainder is left in the pot to be won the next round
  ///
  void decideWinners();

  ///
  /// \brief isRemainder Checks if there is a remainder leftover from splitting the pot
  /// \param _remainder The result of a modulus function
  /// \return A boolean true is returned if there is a remainder
  ///
  bool isRemainder(int _remainder);

  ///
  /// \brief updatePlayer Passes the player information from a vector of m_livePlayers (not folded players), whose life only lasts
  /// for the betting loop to a more permanent vector of players m_table which holds players still in the game.
  /// \param _element allows the element of one vector to be matched with the correct player id of the other vector
  ///
  void updatePlayer(int _element);
//-----------------------------------------------------------------------------------------------------------
//============Get Functions==============================================================================
//-----------------------------------------------------------------------------------------------------------

  ///
  /// \brief getNumPlayers method to access number of players m_numPlayers
  /// \return int m_numPlayers
  ///
  int getNumPlayers()const;

  ///
  /// \brief getLivePlayers method to access the vector of players that haven't folded
  /// \return m_livePlayers
  ///
  std::vector<player> getLivePlayers()const;

  ///
  /// \brief getWinnersIds method to create a vector of the winning players playerIds
  /// \param _winners A vector of the winning players
  /// \return winnerIds A vector of the winners playerIDs
  ///
  std::vector<unsigned int> getWinnerIds(std::vector<player> _winners);


private:

  ///
  /// \brief m_communityCards A vector that stores the 5 public cards
  ///
  cardStack m_communityCards;


  ///
  /// \brief m_numPlayers Number of players in the game
  ///
  int m_numPlayers;

  ///
  /// \brief m_pot The money to be won int the pot
  ///
  unsigned int m_pot;

  ///
  /// \brief m_deck The deck of cards
  ///
  deck m_deck;

  ///
  /// \brief m_dealerGui An instance of GUI
  ///
  GUI::DealerGUI m_dealerGui;

  ///
  /// \brief m_deviceMap
  ///
  Comms::PlayerDevices m_deviceMap;

  ///
  /// \brief m_table A vector of players still in the game
  ///
  std::vector<player> m_table;

  ///
  /// \brief m_livePlayers A vector of players who haven't folded
  ///
  std::vector<player> m_livePlayers;

};

#endif

