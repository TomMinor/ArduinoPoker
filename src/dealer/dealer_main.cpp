#include <iostream>
#include "dealer/pokerHands.h"
#include "dealer/cardStack.h"
#include <stdlib.h>


int main()
{

  int rank;
  int suitFlag;
  int suit;
  card_t card;


  cardStack river;

  rank = rand()%14 +1;
  suitFlag = rand()%4 +4;
  suit = 1<<suitFlag;
  card = rank | suit;
  srand(time(NULL));
  river.addCard(PlayingCard(card));

  rank = rand()%14 +1;
  suitFlag = rand()%4 +4;
  suit = 1<<suitFlag;
  card = rank | suit;
  srand(time(NULL));
  river.addCard(PlayingCard(card));

  rank = rand()%14 +1;
  suitFlag = rand()%4 +4;
  suit = 1<<suitFlag;
  card = rank | suit;
  srand(time(NULL));
  river.addCard(PlayingCard(card));

  rank = rand()%14 +1;
  suitFlag = rand()%4 +4;
  suit = 1<<suitFlag;
  card = rank | suit;
  srand(time(NULL));
  river.addCard(PlayingCard(card));

  rank = rand()%14 +1;
  suitFlag = rand()%4 +4;
  suit = 1<<suitFlag;
  card = rank | suit;
  river.addCard(PlayingCard(card));

//  river.addCard(PlayingCard(Rank::KING,Suit::SPADE));
//  river.addCard(PlayingCard(Rank::SIX,Suit::SPADE));
//  river.addCard(PlayingCard(Rank::FIVE,Suit::SPADE));
//  river.addCard(PlayingCard(Rank::SEVEN,Suit::SPADE));
//  river.addCard(PlayingCard(Rank::THREE,Suit::SPADE));

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
  std::cout<<winners.size()<<" WINNERS:\n";
  for(unsigned int i=0;i<winners.size();i++)
  {
      winners[i].printInfo();
  }

  return 0;

}
