#include <iostream>
#include "dealer/pokerHands.h"

int main()
{
  std::vector<PlayingCard> river;



  river.push_back(PlayingCard(Rank::THREE,Suit::SPADE));
  river.push_back(PlayingCard(Rank::ACE,Suit::SPADE));
  river.push_back(PlayingCard(Rank::ACE,Suit::CLUB));
  river.push_back(PlayingCard(Rank::QUEEN,Suit::SPADE));
  river.push_back(PlayingCard(Rank::KING,Suit::HEART));



  std::vector<player> livePlayers;
  player a,b,c,d;

  a.setHoleCard(PlayingCard(Rank::KING,Suit::DIAMOND));
  a.setHoleCard(PlayingCard(Rank::TWO,Suit::HEART));
  livePlayers.push_back(a);

  b.setHoleCard(PlayingCard(Rank::KING,Suit::DIAMOND));
  b.setHoleCard(PlayingCard(Rank::FIVE,Suit::DIAMOND));
  livePlayers.push_back(b);

  c.setHoleCard(PlayingCard(Rank::NINE,Suit::DIAMOND));
  c.setHoleCard(PlayingCard(Rank::EIGHT,Suit::DIAMOND));
  livePlayers.push_back(c);

  d.setHoleCard(PlayingCard(Rank::FIVE,Suit::DIAMOND));
  d.setHoleCard(PlayingCard(Rank::SEVEN,Suit::SPADE));
  livePlayers.push_back(d);


  //hands::bestHand(livePlayers[0],river);
  hands::winner(livePlayers,river);

  return 0;

}
