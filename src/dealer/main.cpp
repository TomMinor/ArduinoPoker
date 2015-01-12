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
  river.push_back(PlayingCard(Rank::TWO,Suit::HEART));
  river.push_back(PlayingCard(Rank::FIVE,Suit::CLUB));
  river.push_back(PlayingCard(Rank::FOUR,Suit::SPADE));
  river.push_back(PlayingCard(Rank::SIX,Suit::HEART));

  int numPlayers=2;
  std::vector<player> livePlayers(numPlayers);

//  for(int i=0;i<numPlayers;i++)
//  {
//      //livePlayers[i].setScore(4-i);
//      for (int j=0;j<2;j++)
//      {
//          livePlayers[i].setHoleCard(PlayingCard(Rank::ACE,Suit::DIAMOND));
//      }
//  }

livePlayers[0].setHoleCard(PlayingCard(Rank::ACE,Suit::DIAMOND));
livePlayers[0].setHoleCard(PlayingCard(Rank::KING,Suit::DIAMOND));

//livePlayers[1].setHoleCard(PlayingCard(Rank::THREE,Suit::DIAMOND));
//livePlayers[1].setHoleCard(PlayingCard(Rank::FOUR,Suit::DIAMOND));

//livePlayers[1].setHoleCard(PlayingCard(Rank::FIVE,Suit::DIAMOND));
//livePlayers[1].setHoleCard(PlayingCard(Rank::SIX,Suit::DIAMOND));

livePlayers[1].setHoleCard(PlayingCard(Rank::NINE,Suit::DIAMOND));
livePlayers[1].setHoleCard(PlayingCard(Rank::EIGHT,Suit::DIAMOND));



  //hands::bestHand(livePlayers[0],river);
  hands::winner(numPlayers,livePlayers,river);

  return 0;

}
