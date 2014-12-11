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

  std::string getName()const;
  card getCard(const int &_i)const;
  int getScore()const;

public:
  std::string m_name;
  std::vector<card> m_cards;
  int m_score;

};


#endif
