#include <iostream>
#include "dealer/playingcard.h"

int main()
{
  // Construct the card
  PlayingCard card1(Rank::ACE, Suit::SPADE );
  PlayingCard card2(Rank::ACE, Suit::SPADE );

  std::cout << card1 << std::endl;
  std::cout << card2 << std::endl;

  std::cout << bool(card1==card2) << "\n";

  return 0;
}
