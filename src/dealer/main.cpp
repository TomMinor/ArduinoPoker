#include <iostream>
#include "dealer/pokerHands.h"
#include "dealer/cardStack.h"

int main()
{
  cardStack river;



  river.addCard(PlayingCard(Rank::SEVEN,Suit::HEART));
  river.addCard(PlayingCard(Rank::FIVE,Suit::SPADE));
  river.addCard(PlayingCard(Rank::FOUR,Suit::SPADE));
  river.addCard(PlayingCard(Rank::THREE,Suit::SPADE));
  river.addCard(PlayingCard(Rank::TWO,Suit::SPADE));



  std::vector<player> livePlayers;
  player a,b,c,d;

  a.setHoleCard(PlayingCard(Rank::ACE,Suit::DIAMOND));
  a.setHoleCard(PlayingCard(Rank::TWO,Suit::HEART));
  livePlayers.push_back(a);

  b.setHoleCard(PlayingCard(Rank::TWO,Suit::DIAMOND));
  b.setHoleCard(PlayingCard(Rank::THREE,Suit::CLUB));
  livePlayers.push_back(b);

  c.setHoleCard(PlayingCard(Rank::TWO,Suit::CLUB));
  c.setHoleCard(PlayingCard(Rank::SIX,Suit::DIAMOND));
  livePlayers.push_back(c);

  d.setHoleCard(PlayingCard(Rank::SIX,Suit::SPADE));
  d.setHoleCard(PlayingCard(Rank::ACE,Suit::SPADE));
  livePlayers.push_back(d);


  //hands::bestHand(livePlayers[0],river);
  hands::winner(livePlayers,river);

  return 0;

}
