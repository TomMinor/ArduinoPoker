#ifndef _PLAYER__H_
#define _PLAYER__H_

#include <string>
#include <vector>
#include "card.h"

class player
{
public:
  player();
  ~player();

  void setName(const std::string &_name);
  void setCard(const int &_i, const card &_card);
  void setScore(const int &_score);
  void setMoney(const int &_money);
  void takeBet(const int &_bet);
  void receivePot(const int &_pot);

  std::string getName()const;
  card getCard(const int &_i)const;
  int getScore()const;
  int getMoney()const;

private:
  std::string m_name;
  std::vector<card> m_cards;
  int m_score;
  int m_money;

};


#endif
