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



/// \brief A visual representation of a playing card that can be flipped, burned and moved around.
class Card : public Element
{
public:

    /// \brief The card constructor. This probably won't need to be changed much since it is only called automatically by the ElementMaker class.
    /// \param _ren A pointer to the SDL rendering context.
    /// \param _tex A pointer to the SDL texture to use.
    /// \param _srcRect An SDL rectangle that covers the part of the texture the card uses.
    /// \param _destRect An SDL rectangle that specifies the part of the screen to draw the previous rectangle to.
    /// \param _orientation An enum specifying which edge of the screen this card should face.
    /// \param _origin An SDL point specifying the exact location this card should be created. Making sure this is in the centre of _destRect is handled by the ElementMaker
    /// class.
    /// \param _card A "pure data" PlayingCard object from which we can tell the rank and the suit to use.
    /// \return A drawable Card object.
    Card(SDL_Renderer *_ren,
         SDL_Texture *_tex,
         const SDL_Rect &_srcRect,
         const SDL_Rect &_destRect,
         const Orientation &_orient,
         const SDL_Point &_origin,
         const PlayingCard &_card);

    /// \brief Animates the card turning the specified way up.
    /// \param _isFlipped True to turn the card face-down, false for face-up.
    /// \param _instantly True to skip the flipping animation. Useful for setting a card's initial flip state.
    void setFlipped(const bool &_isFlipped, const bool &_instantly = false);

    /// \brief Turns the card face-down, plays a burning animation and marks the card for removal from the game.
    inline void burn() {m_shouldBurn = true;}

    /// \brief A card-specific update function that is needed to implement flipping and burning.
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
