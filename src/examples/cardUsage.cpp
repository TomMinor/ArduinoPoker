#include <iostream>
#include "dealer/playingcard.h"

int main()
{
  // Construct the card
  PlayingCard card(Rank::ACE, Suit::SPADE );

  std::cout << card << "\n";

  return 0;
}
