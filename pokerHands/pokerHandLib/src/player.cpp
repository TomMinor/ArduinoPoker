#include "player.h"


player::player()
{

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

void player::setCard(const int &_i, const card &_card)
{
    m_cards[_i] = _card;
}

void player::setScore(const int &_score)
{
    m_score = _score;
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
//==========Get methods==========
//------------------------------------------------------

std::string player::getName()const
{
    return m_name;
}

card player::getCard(const int &_i)const
{
    return m_cards[_i];
}

int player::getScore()const
{
    return m_score;
}

int player::getMoney()const
{
    return m_money;
}
