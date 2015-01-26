/// \file card.h
/// \brief Low level implementation. Playing card stored in a single byte, used primarily for comms.
/// \author Tom Minor
/// \version 1.0
/// \date 26/1/15 Submitted for assignment deadline
///

#ifndef __CARD_H_
#define __CARD_H_

/* Store suit in left nybble */
#define SUIT_NAMESPACE Suit
namespace SUIT_NAMESPACE
{
  ///
  /// \brief The Value enum stores a playing card suit in a nibble.
  ///
  enum Value
  {
    DIAMOND = (1<<4), // 00010000
    HEART   = (1<<5), // 00100000
    CLUB    = (1<<6), // 01000000
    SPADE   = (1<<7)  // 10000000
  };
}

/* Store rank in right nybble */
namespace Rank
{
  ///
  /// \brief The Value enum stores a playing card rank in a nibble.
  ///
  enum Value
  {
    TWO   = (0x01),
    THREE = (0x02),
    FOUR  = (0x03),
    FIVE  = (0x04),
    SIX   = (0x05),
    SEVEN = (0x06),
    EIGHT = (0x07),
    NINE  = (0x08),
    TEN   = (0x09),
    JACK  = (0x0A),
    QUEEN = (0x0B),
    KING  = (0x0C),
    ACE   = (0x0D)
  };
}

/* Utility macros */

///@brief Checks if card is of club suit.
#define ISCLUB(card)    (card & SUIT_NAMESPACE::CLUB)

///@brief Checks if card is of heart suit.
#define ISHEART(card)   (card & SUIT_NAMESPACE::HEART)

///@brief Checks if card is of spade suit.
#define ISSPADE(card)   (card & SUIT_NAMESPACE::SPADE)

///@brief Checks if card is of diamond suit.
#define ISDIAMOND(card) (card & SUIT_NAMESPACE::DIAMOND)

///@brief The playing card suit information is in the left nibble
#define SUITMASK        (0xF0)

///@brief Extracts the suit of the card
#define SUITOF(card)    (card & SUITMASK)

///@brief Checks if card is a specific suit
#define ISSUIT(card, suit)    (card & suit)

///@brief The playing card rank information is in the right nibble
#define RANKMASK        (0x0F)

///@brief Extracts the rank of the card
#define RANKOF(card)    (card & RANKMASK)

///@brief A macro to convert uint16_t to 2 bytes
#define U16_TO_BYTE_L(U16) ( U16     & 0xFF)
#define U16_TO_BYTE_H(U16) ((U16>>8) & 0xFF)

///@brief A macro to convert 2 bytes to uint16_t
#define BYTE_TO_U16(byte1,byte2)((((uint16_t)byte1)<<8)|byte2)

#endif
