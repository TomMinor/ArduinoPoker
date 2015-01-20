#ifndef _STACK__H_
#define _STACK__H_

#include<vector>
#include "playingcard.h"

/// @author Idris Miles
/// @version 1.0
/// @date 16/01/2015


class cardStack : public std::vector<PlayingCard>
{
public:
  /// @return static bool
  cardStack();
  ~cardStack();

  /// @brief method to add card to stack.
  /// @param [in] const PlayingCard
  void addCard(const PlayingCard &_card);
//--------------------------------------------------------------------------
  /// @brief method to print all cards in stack to standard output stream.
  void printStack()const;
//--------------------------------------------------------------------------

  /// @brief method to access highest card in stack
  /// @return PlayingCard
  PlayingCard getHighestCard();

  /// @brief method to find array ID of a particular card.
  /// @return int (returns -1 if not found)
  int findCard(const PlayingCard &_card);

  /// @brief method to find array ID of a particular rank the first time it appears in stack.
  /// @return int (returns -1 if not found)
  int findRankInStack(const int _rank);

  /// @brief method to find array ID of a particular suit the first time it appears in the stack.
  /// @return int (returns -1 if not found)
  int findSuitInStack(const int _suit);
//--------------------------------------------------------------------------

  /// @brief method to remove a particular card from the stack.
  void removeCard(const PlayingCard &_card);

  /// @brief method to remove a card at a particular index from the stack.
  /// @param [in] const int
  void removeCard(const int _i);

  /// @brief method to empty the stack.
  void emptyStack();
//--------------------------------------------------------------------------

  /// @brief method to replace a card at a particular index with a particular card.
  void replaceCard(const int _i, const PlayingCard &_card);
//--------------------------------------------------------------------------

  /// @brief method to sort the stack of cards in order of highest first.
  void sort();

  /// @brief method to sort the stack of cards in order of lowest first.
  void reverseSort();

  /// @brief method to sort the stack of cards in order of highest first with ACE's being low and put at the end.
  void sortAceLow();
//--------------------------------------------------------------------------
private:
  /// @brief method to check if rank of PlayingCard _a is lower than rank of Playing Card _b.
  /// @param [in] const PlayingCard
  /// @param [in] const PlayingCard
  /// @return static bool
  static bool lowToHigh(const PlayingCard &_a,const PlayingCard &_b);

  /// @brief method to check if rank of PlayingCard _a is bigger than rank of Playing Card _b.
  /// @param [in] const PlayingCard
  /// @param [in] const PlayingCard
  /// @return static bool
  static bool highToLow(const PlayingCard &_a, const PlayingCard &_b);

  /// @brief method to access a particular card in the stack at index _i.
  /// @param [in] const int
  PlayingCard getCard(const int _i) const;

};


#endif
