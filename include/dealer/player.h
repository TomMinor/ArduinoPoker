#ifndef _PLAYER__H_
#define _PLAYER__H_

#include <string>
#include <vector>
#include "playingcard.h"
#include "cardStack.h"

/// @author Idris Miles
/// @version 1.0
/// @date 16/01/2015

class player
{
public:
  player();
  ~player();

  /// @brief method to set players name (m_name).
  /// @param [in] const std::string
  void setName(const std::string &_name);

  /// @brief method to set players Hole card (m_cards),
  /// adds card to back of stack.
  /// @param [in] const PlayingCard
  void setHoleCard(const PlayingCard &_card);

  /// @brief method to set players hand card (m_hand),
  /// adds card to back of stack.
  /// @param [in] const PlayingCard
  void setHandCard(const PlayingCard &_card);

  /// @brief method to set players score (m_score)
  /// @param [in] const int
  void setScore(const int &_score);

  /// @brief method to set playesr kicker (m_kicker)
  /// @param [in] const int
  void setKicker(const int &_kicker);

  /// @brief method to set players money (m_money)
  /// @param [in] const int
  void setMoney(const int &_money);

  /// @brief method to set players bet (m_bet)
  /// @param [in] const int
  void takeBet(const int &_bet);

  /// @brief method to add betting money to players money.
  /// @param [in] const PlayingCard
  void receivePot(const int &_pot);
//------------------------------------------------------------
  /// @brief method to remove last card in players poker hand stack.
  void removeLastHandCard();

  /// @brief method to remove particular card by index from players poker hand stack.
  /// @param [in] const int
  void removeHandCard(const int _i);

  /// @brief method to remove particular card from players poker hand stack.
  /// @param [in] const PlayingCard
  void removeHandCard(const PlayingCard &_card);

  /// @brief method to empty players Hand stack.
  void emptyHand();

  /// @brief method to remove last card in players Hole card stack
  void removeLastHoleCard();

  /// @brief method to remove particular card by index from the players Hole card stack.
  /// @param [in] const int
  void removeHoleCard(const int _i);

  /// @brief method to remove particular card from the players Hole card stack.
  /// @param [in] const PlayingCard
  void removeHoleCard(const PlayingCard &_card);

  /// @brief method to empty players Hole card stack.
  void emptyHole();
//------------------------------------------------------------
  /// @brief method to access players name (m_name).
  /// @return std::string
  std::string getName()const;

  /// @brief method to access a particular card from players Hole cards (m_cards[i]),
  /// 2 cards dealers gives player at start of game.
  /// @param [in] const int
  /// @return PlayingCard
  PlayingCard getHoleCard(const int &_i)const;

  /// @brief method to access the stack of players Hole cards (m_cards).
  /// @return cardStack
  cardStack getHole()const;

  /// @brief method to access a particular card from the players poker hand (m_hand[i]).
  /// @param [in] const int
  /// @return PlayingCard
  PlayingCard getHandCard(const int &_i)const;

  /// @brief method to access the stack of players poker hand cards (m_hand).
  /// @return cardStack
  cardStack getHand() const;

  /// @brief method to access the number of cards in the players poker hand.
  /// @return int
  int getNumCards()const;

  /// @brief method to access the players score (m_score)
  /// @return int
  int getScore()const;

  /// @brief method to acces the players kicker (m_kicker)
  /// @return int
  int getKicker()const;

  /// @brief method to access the players money (m_money)
  /// @return int
  int getMoney()const;

  /// @brief method to print the players info including:
  /// players name (m_name), score (m_score), kicker (m_kicker) and poker hand (m_hand)
  void printInfo()const;

  ///@brief method to access the players bet amount (m_bet)
  /// @return int
  int getBet()const;


  cardStack m_hand;
  bool fold;


private:
  std::string m_name;
  cardStack m_cards;
  int m_score;
  int m_kicker;
  int m_money;
  int m_bet;
protected:


};


#endif
