#ifndef _PLAYER__H_
#define _PLAYER__H_

#include <string>
#include <vector>
#include "playingcard.h"
#include "cardStack.h"

class player
{
public:
  player();
  ~player();

  void setName(const std::string &_name);
  void setHoleCard(const PlayingCard &_card);
  void setHandCard(const PlayingCard &_card);
  void setScore(const int &_score);
  void setKicker(const int &_kicker);
  void setMoney(const int &_money);
  void takeBet(const int &_bet);
  void receivePot(const int &_pot);

  void removeLastHandCard();
  void removeHandCard(const int _i);
  void removeHandCard(const PlayingCard &_card);
  void removeLastHoleCard();
  void removeHoleCard(const int _i);
  void removeHoleCard(const PlayingCard &_card);
  void emptyHand();

  std::string getName()const;
  PlayingCard getHoleCard(const int &_i)const;
  cardStack getHole()const;
  PlayingCard getHandCard(const int &_i)const;
  cardStack getHand() const;
  int getNumCards()const;
  int getScore()const;
  int getKicker()const;
  int getMoney()const;

  void printInfo()const;



private:
  std::string m_name;
  cardStack m_cards;
  cardStack m_hand;
  int m_score;
  int m_kicker;
  int m_money;

};


#endif
