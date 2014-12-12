#ifndef CARD_H
#define CARD_H

#include <cstdlib>
#include <SDL2/SDL.h>
#include <iostream>

#include "element.h"

<<<<<<< HEAD
//vars SDL deals with that will be the same for most cards
=======
//vars that will be the same for most cards
>>>>>>> 9a857e697db5c34734e45771dbf4daa043b18f26
typedef struct
{
    SDL_Renderer *ren;
    SDL_Texture *texture;
<<<<<<< HEAD
=======
    unsigned int scale;
>>>>>>> 9a857e697db5c34734e45771dbf4daa043b18f26
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
<<<<<<< HEAD
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

=======
    SPADES,
    HEARTS,
    DIAMONDS
} Suit;

>>>>>>> 9a857e697db5c34734e45771dbf4daa043b18f26
class Card : public Element
{
public:
    Card(SDL_Renderer *_ren,
         SDL_Texture *_tex,
<<<<<<< HEAD
         const SDL_Rect &_srcRect,
         const SDL_Rect &_destRect,
         const Orientation &_orient,
         const CardType &_type);
    inline void setFlipped(const bool &_isFlipped) {m_isFlipped = _isFlipped;}
    inline void burn() {m_shouldBurn = true;}
=======
         SDL_Rect _srcRect,
         SDL_Rect _destRect,
         Orientation _orient,
         Rank _rank,
         Suit _suit);
    inline void setFlipped(bool _isFlipped) {m_isFlipped = _isFlipped;}
>>>>>>> 9a857e697db5c34734e45771dbf4daa043b18f26
    virtual void update(); //implement flipping
    virtual void draw(); //implement X offset

private:
    bool m_isFlipped;
    float m_flippedAmount;
    int m_xOffset;//used to offset the rect while the card is flipping to give the illusion of flipping around its centre
    Rank m_rank;
    Suit m_suit;
<<<<<<< HEAD
    bool m_shouldBurn;
    bool m_burned;
    int m_burnLevel;
    void continueFlip();
=======
>>>>>>> 9a857e697db5c34734e45771dbf4daa043b18f26
};

#endif // CARD_H
