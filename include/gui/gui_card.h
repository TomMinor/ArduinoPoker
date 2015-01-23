#ifndef CARD_H
#define CARD_H

#include <cstdlib>
#include <SDL2/SDL.h>
#include <iostream>

#include "gui_element.h"
#include "dealer/playingcard.h"

namespace GUI
{

/// \brief This struct contains variables for SDL that will be the same for all cards, which we therefore won't want to send to the constructor individually every time.
typedef struct
{
    SDL_Renderer *ren;
    SDL_Texture *texture;
    unsigned int cardWidth;
    unsigned int cardHeight;
} CardInfo;

//obselete
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

//also obselete!
typedef enum
{
    CLUBS,
    SPADES,
    HEARTS,
    DIAMONDS
} Suit;

//stuff we need to know to create a particular card
//GUESS WHAT
//OBSELETE
typedef struct
{
    Rank rank;
    Suit suit;
} CardType;

/// \brief A visual representation of a playing card that can be flipped, burned and moved around.
class Card : public Element
{
public:
    Card(SDL_Renderer *_ren,
         SDL_Texture *_tex,
         const SDL_Rect &_srcRect,
         const SDL_Rect &_destRect,
         const Orientation &_orient,
         const SDL_Point &_origin,
         const PlayingCard &_card);
    void setFlipped(const bool &_isFlipped, const bool &_instantly = false);
    inline void burn() {m_shouldBurn = true;}
    virtual void update(); //implement flipping

private:
    bool m_isFlipped;
    float m_flippedAmount;
    PlayingCard m_cardType;
    bool m_shouldBurn;
    int m_burnLevel;
    int continueFlip();
    int m_xOffset;
};

}

#endif // CARD_H
