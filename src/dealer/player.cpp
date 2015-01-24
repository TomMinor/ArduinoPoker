#include "dealer/player.h"
#include <iostream>

player::player()
{
    m_score = 0;
    m_kicker = 0;
    m_money = 1000;
    fold = false;

}

player::~player()
{

}

//------------------------------------------------------
//==========Set methods==========
//------------------------------------------------------
void player::setName(const std::string &_name)
{
    m_name = _name;
}

void player::setHoleCard(const PlayingCard &_card)
{
    m_cards.addCard(_card);
}

void player::setHandCard(const PlayingCard &_card)
{
    m_hand.addCard(_card);
}

void player::setScore(const int &_score)
{
    m_score = _score;
}

void player::setKicker(const int &_kicker)
{
    m_kicker = _kicker;
}

void player::setMoney(const int &_money)
{
    m_money = _money;
}

void player::takeBet(const int &_bet)
{
    m_money -= _bet;
}

void player::receivePot(const int &_pot)
{
    m_money += _pot;
}

//------------------------------------------------------
//=======Remove cards============
//------------------------------------------------------
void player::removeLastHandCard()
{
    m_hand.pop_back();
}
void player::removeHandCard(const int _i)
{
  m_hand.removeCard(_i);
}

void player::removeHandCard(const PlayingCard &_card)
{
  m_hand.removeCard(_card);
}

void player::emptyHand()
{
  m_hand.emptyStack();
}

void player::removeLastHoleCard()
{
    m_cards.pop_back();
}
void player::removeHoleCard(const int _i)
{
  m_cards.removeCard(_i);
}

void player::removeHoleCard(const PlayingCard &_card)
{
  m_cards.removeCard(_card);
}

void player::emptyHole()
{
  m_cards.emptyStack();
}

//------------------------------------------------------
//==========Get methods==========
//------------------------------------------------------
std::string player::getName()const
{
    return m_name;
}

PlayingCard player::getHoleCard(const int &_i)const
{
    return m_cards[_i];
}

cardStack player::getHole()const
{
    return m_cards;
}

PlayingCard player::getHandCard(const int &_i)const
{
    return m_hand[_i];
}

cardStack player::getHand()const
{
    return m_hand;
}

int player::getNumCards()const
{
    return m_hand.size();
}

int player::getScore()const
{
    return m_score;
}

int player::getKicker()const
{
    return m_kicker;
}

int player::getMoney()const
{
    return m_money;
}

int player::getBet()const
{
  return m_bet;
}

//--------------------------------------------------------------------
void player::printInfo()const
{
  std::cout<<getName()<<" | ";
  std::cout<<"score of: "<<getScore()<<" | ";
  std::cout<<"kicker of: "<<getKicker()<<"\n";
  getHand().printStack();
  std::cout<<"\n";
}
