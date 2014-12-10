#ifndef CARD_H
#define CARD_H

#include <cstdlib>
#include <SDL2/SDL.h>
#include <iostream>

#include "element.h"

//vars that will be the same for most cards
typedef struct
{
    SDL_Renderer *ren;
    SDL_Texture *texture;
    unsigned int scale;
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
    SPADES,
    HEARTS,
    DIAMONDS
} Suit;

class Card : public Element
{
public:
    Card(SDL_Renderer *_ren,
         SDL_Texture *_tex,
         SDL_Rect _srcRect,
         SDL_Rect _destRect,
         Orientation _orient,
         Rank _rank,
         Suit _suit);
    inline void setFlipped(bool _isFlipped) {m_isFlipped = _isFlipped;}
    virtual void update(); //implement flipping
    virtual void draw(); //implement X offset

private:
    bool m_isFlipped;
    float m_flippedAmount;
    int m_xOffset;//used to offset the rect while the card is flipping to give the illusion of flipping around its centre
    Rank m_rank;
    Suit m_suit;
};

#endif // CARD_H
