#include "dealer/deck.h"


deck::deck()
{
  for(int i = Rank::TWO; i<=Rank::ACE; i++)
  {
      m_pack.push_back(PlayingCard((Rank::Value) i, Suit::DIAMOND));
  }

  for(int i = Rank::TWO; i<=Rank::ACE; i++)
  {
      m_pack.push_back(PlayingCard((Rank::Value)i, Suit::HEART));
  }

  for(int i = Rank::TWO; i<=Rank::ACE; i++)
  {
      m_pack.push_back(PlayingCard((Rank::Value)i, Suit::CLUB));
  }

  for(int i = Rank::TWO; i<=Rank::ACE; i++)
  {
      m_pack.push_back(PlayingCard((Rank::Value)i, Suit::SPADE));
  }
}


deck ::~deck()
{

}

void deck::init()
{

}

void deck::reset()
{

}

void deck::shuffle()
{
  std::random_shuffle(m_pack.begin(), m_pack.end());
}

PlayingCard deck::deal()
{
  PlayingCard a = m_pack[m_pack.size()-1];
  m_pack.pop_back();

  return a;
}
