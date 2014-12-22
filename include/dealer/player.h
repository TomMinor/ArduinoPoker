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
  void setHandCard(const PlayingCard &_card);
  void setScore(const int &_score);
  void setMoney(const int &_money);
  void takeBet(const int &_bet);
  void receivePot(const int &_pot);

  void popHandCard();

  std::string getName()const;
  PlayingCard getCard(const int &_i)const;
  PlayingCard getHandCard(const int &_i)const;
  std::vector<PlayingCard> getHand()const;
  int getNumCards()const;
  int getScore()const;
  int getMoney()const;



private:
  std::string m_name;
  std::vector<PlayingCard> m_cards;
  std::vector<PlayingCard> m_hand;
  int m_score;
  int m_tieScore;
  int m_money;

};


#endif
