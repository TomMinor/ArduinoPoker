#ifndef __CARD_H_
#define __CARD_H_

/* Store suit in left nybble */
#define SUIT_NAMESPACE Suit
namespace SUIT_NAMESPACE
{
  enum Value
  {
    DIAMOND = (1<<4),
    HEART   = (1<<5),
    CLUB    = (1<<6),
    SPADE   = (1<<7)
  };
}

/* Store rank in right nybble */
namespace Rank
{
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
    JACK  = (0x09),
    QUEEN = (0x0A),
    KING  = (0x0B),
    ACE   = (0x0C),
  };
}

/* Utility macros*/
#define ISCLUB(card)    (card & SUIT_NAMESPACE::CLUB)
#define ISHEART(card)   (card & SUIT_NAMESPACE::HEART)
#define ISSPADE(card)   (card & SUIT_NAMESPACE::SPADE)
#define ISDIAMOND(card) (card & SUIT_NAMESPACE::DIAMOND)
#define SUITMASK (0xF0)
#define SUITOF(card)    (card & SUITMASK)

#define RANKMASK (0x0F)
#define RANKOF(card) (card & RANKMASK)

#endif
