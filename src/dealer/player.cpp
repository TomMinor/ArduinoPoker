#include "dealer/player.h"


player::player()
{
    m_score = 0;
    m_kicker = 0;

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
    m_cards.push_back(_card);
}

void player::setHandCard(const PlayingCard &_card)
{
    m_hand.push_back(_card);
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


void player::popHandCard()
{
    m_hand.pop_back();
}
void player::popHoleCard()
{
    m_cards.pop_back();
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

std::vector<PlayingCard> player::getHole()const
{
    return m_cards;
}

PlayingCard player::getHandCard(const int &_i)const
{
    return m_hand[_i];
}

std::vector<PlayingCard> player::getHand()const
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
