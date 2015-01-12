#ifndef _STACK__H_
#define _STACK__H_
#include<vector>
#include "playingcard.h"

class cardStack : public std::vector<PlayingCard>
{
public:
  cardStack();
  ~cardStack();

  void addCard(const PlayingCard &_card);

  PlayingCard getHighestCard();
  int findCard(const PlayingCard &_card);
  int findRankInStack(const int _rank);
  int findSuitInStack(const int _suit);

  void removeCard(const PlayingCard &_card);
  void removeCard(const int _i);
  void emptyStack();

  void replaceCard(const int _i, const PlayingCard &_card);

  void sort();
  void reverseSort();
  void sortAceLow();

private:
  static bool lowToHigh(const PlayingCard &_a,const PlayingCard &_b);
  static bool highToLow(const PlayingCard &_a, const PlayingCard &_b);
  PlayingCard getCard(const int _i);

};


#endif
