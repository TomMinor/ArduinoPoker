#include "dealer/deck.h"



deck::deck()
{
  initDeck();
}


deck ::~deck()
{

}

void deck::initDeck()
{
  for(int i = Rank::TWO; i<=Rank::ACE; i++)
  {
      m_pack.push_back(PlayingCard((Rank::Value)i, Suit::DIAMOND));
      m_pack.push_back(PlayingCard((Rank::Value)i, Suit::HEART));
      m_pack.push_back(PlayingCard((Rank::Value)i, Suit::CLUB));
      m_pack.push_back(PlayingCard((Rank::Value)i, Suit::SPADE));
  }
}

void deck::reset()
{
  m_pack.erase(m_pack.begin(),m_pack.end());
  initDeck();
  shuffle();
}

void deck::shuffle()
{
  std::random_shuffle(m_pack.begin(), m_pack.end());
}

PlayingCard deck::deal()
{
  PlayingCard topCard = m_pack[m_pack.size()-1];
  m_pack.pop_back();

  return topCard;
}

void deck::printDeck()
{
  cardStack::iterator it;

  for(it=m_pack.begin(); it!=m_pack.end(); it++)
  {
    std::cout<<*it<<"\n";
  }

}
