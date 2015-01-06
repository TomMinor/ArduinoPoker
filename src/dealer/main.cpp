#include <iostream>
#include "dealer/pokerHands.h"

int main()
{
  std::vector<PlayingCard> river;

//  for(int i=0;i<5;i++)
//  {
//      river.push_back(PlayingCard(Rank::TEN,Suit::SPADE));
//  }

  river.push_back(PlayingCard(Rank::THREE,Suit::SPADE));
  river.push_back(PlayingCard(Rank::THREE,Suit::HEART));
  river.push_back(PlayingCard(Rank::THREE,Suit::CLUB));
  river.push_back(PlayingCard(Rank::KING,Suit::SPADE));
  //river.push_back(PlayingCard(Rank::FOUR,Suit::HEART));



  std::vector<player> livePlayers;
  player a,b,c,d;

  a.setHoleCard(PlayingCard(Rank::QUEEN,Suit::DIAMOND));
  a.setHoleCard(PlayingCard(Rank::TWO,Suit::DIAMOND));
  livePlayers.push_back(a);

  b.setHoleCard(PlayingCard(Rank::TWO,Suit::DIAMOND));
  b.setHoleCard(PlayingCard(Rank::THREE,Suit::DIAMOND));
  livePlayers.push_back(b);

  c.setHoleCard(PlayingCard(Rank::TWO,Suit::DIAMOND));
  c.setHoleCard(PlayingCard(Rank::FOUR,Suit::DIAMOND));
  livePlayers.push_back(c);

  d.setHoleCard(PlayingCard(Rank::TWO,Suit::DIAMOND));
  d.setHoleCard(PlayingCard(Rank::FOUR,Suit::DIAMOND));
  livePlayers.push_back(d);


  //hands::bestHand(livePlayers[0],river);
  hands::winner(livePlayers,river);

  return 0;

}
