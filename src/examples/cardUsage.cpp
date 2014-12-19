#include <iostream>
#include "dealer/playingcard.h"

int main()
{
  // Construct the card
  PlayingCard card1(Rank::ACE, Suit::SPADE );
  PlayingCard card2(Rank::ACE, Suit::SPADE );
  PlayingCard card3(Rank::JACK, Suit::DIAMOND );

  std::cout << "Rank of card1 is " << card1.RankString() << "\n";
  std::cout << "Suit of card1 is " << card1.SuitString() << "\n";

  std::cout << card1 << std::endl;
  std::cout << card2 << std::endl;
  std::cout << card3 << std::endl;

  std::cout << "Cards " << (card1==card2 ? "are not" : "are") << " equal\n";
  std::cout << "Cards " << (card1!=card2 ? "are" : "are not") << " equal\n";

  std::cout << bool(card1.IsRank(Rank::ACE)) << std::endl;

  return 0;
}
