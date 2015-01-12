#ifndef _PLAYER__H_
#define _PLAYER__H_

#include <string>
#include <vector>
#include "playingcard.h"

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

  void popHandCard();

  std::string getName()const;
  PlayingCard getHoleCard(const int &_i)const;
  PlayingCard getHandCard(const int &_i)const;
  std::vector<PlayingCard> getHand()const;
  int getNumCards()const;
  int getScore()const;
  int getKicker()const;
  int getMoney()const;



private:
  std::string m_name;
  std::vector<PlayingCard> m_cards;
  std::vector<PlayingCard> m_hand;
  int m_score;
  int m_kicker;
  int m_money;

};


#endif
