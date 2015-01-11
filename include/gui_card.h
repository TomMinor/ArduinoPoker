#ifndef CARD_H
#define CARD_H

#include <cstdlib>
#include <SDL2/SDL.h>
#include <iostream>

#include "gui_element.h"

//vars SDL deals with that will be the same for most cards
typedef struct
{
    SDL_Renderer *ren;
    SDL_Texture *texture;
    unsigned int cardWidth;
    unsigned int cardHeight;
} GUI_CardInfo;

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
} GUI_Rank;

typedef enum
{
    CLUBS,
    SPADES,
    HEARTS,
    DIAMONDS
} GUI_Suit;

//stuff we need to know to create a particular card
typedef struct
{
    GUI_Rank rank;
    GUI_Suit suit;
} GUI_CardType;

class GUI_Card : public GUI_Element
{
public:
    GUI_Card(SDL_Renderer *_ren,
         SDL_Texture *_tex,
         const SDL_Rect &_srcRect,
         const SDL_Rect &_destRect,
         const GUI_Orientation &_orient,
         const SDL_Point &_origin,
         const GUI_CardType &_type);
    inline void setFlipped(const bool &_isFlipped) {m_isFlipped = _isFlipped;}
    inline void burn() {m_shouldBurn = true;}
    virtual void update(); //implement flipping
    virtual inline void kill() {m_shouldKillNow = true;}

private:
    bool m_isFlipped;
    float m_flippedAmount;
    GUI_Rank m_rank;
    GUI_Suit m_suit;
    bool m_shouldBurn;
    int m_burnLevel;
    void continueFlip();
};

#endif // CARD_H
