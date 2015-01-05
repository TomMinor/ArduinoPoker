<<<<<<< HEAD
#ifndef CARD_H
#define CARD_H

#include <cstdlib>
#include <SDL2/SDL.h>
#include <iostream>

#include "element.h"

//vars SDL deals with that will be the same for most cards
typedef struct
{
    SDL_Renderer *ren;
    SDL_Texture *texture;
    unsigned int cardWidth;
    unsigned int cardHeight;
} CardInfo;

typedef enum
{
    ACE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING
} Rank;

typedef enum
{
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES,
} Suit;

//stuff we need to know to create a particular card
typedef struct
{
    Rank rank;
    Suit suit;
} CardType;

class Card : public Element
{
public:
    Card(SDL_Renderer *_ren,
         SDL_Texture *_tex,
         const SDL_Rect &_srcRect,
         const SDL_Rect &_destRect,
         const Orientation &_orient,
         const SDL_Point &_origin,
         const CardType &_type);
    inline void setFlipped(const bool &_isFlipped) {m_isFlipped = _isFlipped;}
    inline void burn() {m_shouldBurn = true;}
    virtual void update(); //implement flipping
    virtual void draw(); //implement X offset

private:
    bool m_isFlipped;
    float m_flippedAmount;
    int m_xOffset;//used to offset the rect while the card is flipping to give the illusion of flipping around its centre
    Rank m_rank;
    Suit m_suit;
    bool m_shouldBurn;
    int m_burnLevel;
    void continueFlip();
};

#endif // CARD_H
=======
#ifndef __CARD_H_
#define __CARD_H_

/* Store suit in left nybble */
#define SUIT_NAMESPACE Suit
namespace SUIT_NAMESPACE
{
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
    TEN   = (0x0A),
    JACK  = (0x0B),
    QUEEN = (0x0C),
    KING  = (0x0D)
  };
}

/* Utility macros*/
#define ISCLUB(card)    (card & SUIT_NAMESPACE::CLUB)
#define ISHEART(card)   (card & SUIT_NAMESPACE::HEART)
#define ISSPADE(card)   (card & SUIT_NAMESPACE::SPADE)
#define ISDIAMOND(card) (card & SUIT_NAMESPACE::DIAMOND)

#define ISSUIT(card, suit)    (card & suit)

#define RANKMASK        (0x0F)
#define RANKOF(card)    (card & RANKMASK)

#endif
>>>>>>> b14a25bfb7c9ebf6e4ddf288a11bf7fff0a8999d
