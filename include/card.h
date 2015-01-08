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
