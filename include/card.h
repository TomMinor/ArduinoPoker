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
    ACE   = (0x01),
    TWO   = (0x02),
    THREE = (0x03),
    FOUR  = (0x04),
    FIVE  = (0x05),
    SIX   = (0x06),
    SEVEN = (0x07),
    EIGHT = (0x08),
    NINE  = (0x09),
    JACK  = (0x0A),
    QUEEN = (0x0B),
    KING  = (0x0C)
  };
}

/* Utility macros*/
#define ISCLUB(card)    (card & SUIT_NAMESPACE::CLUB)
#define ISHEART(card)   (card & SUIT_NAMESPACE::HEART)
#define ISSPADE(card)   (card & SUIT_NAMESPACE::SPADE)
#define ISDIAMOND(card) (card & SUIT_NAMESPACE::DIAMOND)

#define RANKMASK (0x0F)
#define RANKOF(card) (card & RANKMASK)

#endif
