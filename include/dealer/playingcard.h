/// \file playingcard.h
/// \brief Encapsulates the low-level byte sized card defined in card.h in a user friendly class.
/// Provides lookup functions for easy printing and comparison functions.
/// \author Tom Minor, modified by Dealer team (Idris Miles)
/// \version 1.1
/// \date 26/1/15 Submitted for assignment deadline
///

#ifndef __DEALER_PLAYINGCARD_H_
#define __DEALER_PLAYINGCARD_H_

#include <string>
#include <stdint.h>

#include "../shared/card.h"

///
/// \brief card_t Represents a card with a single byte
///
typedef uint8_t card_t;

///
/// \brief RankLookup A lookup for table for the rank's string representation
///
extern const std::string RankLookup[13];

///
/// \brief SuitLookup A lookup for table for the suit's string representation
///
extern const std::string SuitLookup[4];

///
/// \brief The PlayingCard class
/// The PlayingCard class encapsulates the single byte card representation defined in "card.h".
/// It overloads various operators for ease of playing card comparison and provides string lookup tables for
/// string representations of the card.
///
class PlayingCard
{
public:
  ///
  /// \brief PlayingCard
  /// \param _rank
  /// \param _suit
  ///
  PlayingCard(Rank::Value _rank, Suit::Value _suit);

  ///
  /// \brief PlayingCard
  /// \param _value
  ///
  PlayingCard(card_t _value);

  ///
  /// \brief IsRank
  /// \param _rank
  /// \return True if _rank equals the playing card's rank
  ///
  bool IsRank(Rank::Value _rank) const;

  ///
  /// \brief IsSuit
  /// \param _suit
  /// \return True if _rank equals the playing card's suit
  ///
  bool IsSuit(Suit::Value _suit) const;

  ///
  /// \brief RankString
  /// \return The string representation of the playing card's rank.
  ///
  std::string RankString() const;

  ///
  /// \brief SuitString
  /// \return The string representation of the playing card's suit.
  ///
  std::string SuitString() const;

  ///
  /// \brief getRank getter for the card's rank.
  /// \return the numerical value of the card's rank.
  ///
  int getRank()const;

  ///
  /// \brief getSuit getter for the card's suit.
  /// \return the numerical value of the card's suit (0 - 3), returns -1 if the suit is invalid.
  ///
  int getSuit() const;

  ///
  /// \brief getSuitValue Getter for the card's actual suit value.
  /// \return the suit's value.
  ///
  int getSuitValue()const;

  ///
  /// \brief getValue Getter for the card's byte value
  /// \return The card's raw byte data.
  ///
  card_t getValue()const;

  ///
  /// \brief operator = Card assignment operator.
  /// \param _card The card to set the value of this to.
  ///
  void operator=(const PlayingCard &_card);

  ///
  /// \brief operator == Equality operator.
  /// \param _card The card to check against.
  /// \return True if both cards are identical.
  ///
  bool operator==(const PlayingCard& _card)const;

  ///
  /// \brief operator != Inequality operator.
  /// \param _card The card to check against.
  /// \return True if either rank or suit do not match.
  ///
  bool operator!=(const PlayingCard& _card)const;

  ///
  /// \brief operator << Returns a stream containing a string with the format "<RankString()> of <SuitString()>'s"
  /// \param _stream
  /// \param _card The card whose value will be printed.
  /// \return a reference to a stream.
  ///
  friend std::ostream& operator<<(std::ostream& _stream, const PlayingCard& _card);

private:  
  ///
  /// \brief m_value m_value Stores the suit and rank of the playing card in a single byte.
  ///
  card_t m_value;

};

#endif
