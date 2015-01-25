#ifndef _DECK__H_
#define _DECK__H_

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#include "playingcard.h"
#include <algorithm>
#include "dealer/cardStack.h"


class deck
{

public:
  ///
  /// \brief deck constructor calls a function to initialise the deck
  ///
  deck();
  ~deck();

  ///
  /// \brief initDeck Adds all the cards to the deck
  ///
  void initDeck();

  ///
  /// \brief removes all the cards from the deck, refills it and then shuffles the deck
  ///
  void reset();

  ///
  /// \brief shuffle Uses a function built into the algorithm library that shuffles a vector
  ///
  void shuffle();

  ///
  /// \brief printDeck prints out all element of the deck to the screen.
  ///
  void printDeck();

  ///
  /// \brief deal Pops off a card from the end of the vector and returns it
  /// \return topCard The card at the top of the deck
  ///
  PlayingCard deal();

private:

  ///
  /// \brief m_pack a vector of cards that represents the deck ofcards
  ///
  cardStack m_pack;

};

#endif
