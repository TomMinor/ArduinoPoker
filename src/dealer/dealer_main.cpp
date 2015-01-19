#include <iostream>
#include "dealer/pokerHands.h"
#include "dealer/cardStack.h"

//int main()
//{
//  cardStack river;
//  river.addCard(PlayingCard(Rank::KING,Suit::SPADE));
//  river.addCard(PlayingCard(Rank::QUEEN,Suit::DIAMOND));
//  river.addCard(PlayingCard(Rank::QUEEN,Suit::SPADE));
//  river.addCard(PlayingCard(Rank::ACE,Suit::SPADE));
//  river.addCard(PlayingCard(Rank::TWO,Suit::DIAMOND));

////---------------------------------------------------------


//  std::vector<player> livePlayers;
//  player a,b,c,d;
////---------------------------------------------------------
//  // Player: 0
//  a.setHoleCard(PlayingCard(Rank::FOUR,Suit::DIAMOND));
//  a.setHoleCard(PlayingCard(Rank::TWO,Suit::HEART));
//  livePlayers.push_back(a);
////---------------------------------------------------------
//  // Player: 1
//  b.setHoleCard(PlayingCard(Rank::KING,Suit::DIAMOND));
//  b.setHoleCard(PlayingCard(Rank::SIX,Suit::CLUB));
//  livePlayers.push_back(b);
////---------------------------------------------------------
//  // Player: 2
//  c.setHoleCard(PlayingCard(Rank::KING,Suit::CLUB));
//  c.setHoleCard(PlayingCard(Rank::NINE,Suit::DIAMOND));
//  livePlayers.push_back(c);
////---------------------------------------------------------
//  // Player: 3
//  d.setHoleCard(PlayingCard(Rank::NINE,Suit::SPADE));
//  d.setHoleCard(PlayingCard(Rank::NINE,Suit::HEART));
//  livePlayers.push_back(d);

////---------------------------------------------------------

//  std::vector<player> winners;
//  winners = hands::winner(livePlayers,river);
//  std::cout<<winners.size()<<" Winners\n";

//  return 0;

//}
int main()
{
  cardStack river;
  river.addCard(PlayingCard(Rank::KING,Suit::SPADE));
  river.addCard(PlayingCard(Rank::SIX,Suit::DIAMOND));
  river.addCard(PlayingCard(Rank::FIVE,Suit::SPADE));
  river.addCard(PlayingCard(Rank::FOUR,Suit::SPADE));
  river.addCard(PlayingCard(Rank::THREE,Suit::SPADE));

//---------------------------------------------------------

  std::vector<player> livePlayers;
  player a,b,c,d;
//---------------------------------------------------------
  // Player: 0
  a.setName("Alan");
  a.setHoleCard(PlayingCard(Rank::FOUR,Suit::DIAMOND));
  a.setHoleCard(PlayingCard(Rank::TWO,Suit::HEART));
  //livePlayers.push_back(a);
//---------------------------------------------------------
  // Player: 1
  b.setName("Ben");
  b.setHoleCard(PlayingCard(Rank::KING,Suit::DIAMOND));
  b.setHoleCard(PlayingCard(Rank::SIX,Suit::CLUB));
  //livePlayers.push_back(b);
//---------------------------------------------------------
  // Player: 2
  c.setName("Charlie");
  c.setHoleCard(PlayingCard(Rank::KING,Suit::CLUB));
  c.setHoleCard(PlayingCard(Rank::NINE,Suit::DIAMOND));
  //livePlayers.push_back(c);
//---------------------------------------------------------
  // Player: 3
  d.setName("Dave");
  d.setHoleCard(PlayingCard(Rank::TWO,Suit::SPADE));
  d.setHoleCard(PlayingCard(Rank::ACE,Suit::SPADE));
  livePlayers.push_back(d);
//---------------------------------------------------------

  std::vector<player> winners;
  winners = hands::winner(livePlayers,river);
  std::cout<<winners.size()<<" Winners\n";
  for(unsigned int i=0;i<winners.size();i++)
  {
      winners[i].printInfo();
  }

  return 0;

}
