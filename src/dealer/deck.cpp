#include "dealer/deck.h"


//constructor
deck::deck()
{
  //initialise deck
  initDeck();
}

//destructor
deck ::~deck()
{

}

//add all cards to the deck
void deck::initDeck()
{
  //loop through the cards ranks and add the card for each suit
  for(int i = Rank::TWO; i<=Rank::ACE; i++)
  {
      m_pack.push_back(PlayingCard((Rank::Value)i, Suit::DIAMOND));
      m_pack.push_back(PlayingCard((Rank::Value)i, Suit::HEART));
      m_pack.push_back(PlayingCard((Rank::Value)i, Suit::CLUB));
      m_pack.push_back(PlayingCard((Rank::Value)i, Suit::SPADE));
  }
}

//reset the deck
void deck::reset()
{
  //remove all cards from the deck
  m_pack.erase(m_pack.begin(),m_pack.end());
  //re add cards
  initDeck();
  //shuffle the deck
  shuffle();
}

//uses a function built into the algorithm library to shuffle a vector
void deck::shuffle()
{
  std::srand( unsigned ( std::time(0) ) );

  std::random_shuffle(m_pack.begin(), m_pack.end());
}

//pop off the top card of the deck and return it
PlayingCard deck::deal()
{
  PlayingCard topCard = m_pack[m_pack.size()-1];
  m_pack.pop_back();

  return topCard;
}

//prints all the cards in the deck - used for debugging
void deck::printDeck()
{
  cardStack::iterator it;

  for(it=m_pack.begin(); it!=m_pack.end(); it++)
  {
    std::cout<<*it<<"\n";
  }

}
