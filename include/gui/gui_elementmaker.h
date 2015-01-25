#ifndef ELEMENTMAKER_H
#define ELEMENTMAKER_H

#include <SDL.h>
#include "gui_element.h"
#include "gui_card.h"
#include "gui_label.h"

namespace GUI
{

/// \brief This class serves as a factory for dynamically allocated visual elements.
///
/// This layer of abstraction is needed because each type of visual element should ideally have a specialised constructor, but they are derived from the same class and
/// C++ does not support virtual constructors.
class ElementMaker
{
public:
    /// \brief The constructor.
    /// \param _cardInfo A pointer to a struct containing all the constant information for cards so we don't have to receive it every time we make a card.
    /// \param _cardInfo A pointer to a struct containing all the constant information for labels so we don't have to receive it every time we make a label.
    /// \return An ElementMaker object.
    ElementMaker(const CardInfo* _cardInfo, const LabelFormat* _labelFormat);

    /// \brief Constructs a dynamically allocated element using the given parameters. This function assumes the entire texture will be drawn 1:1, as opposed to the other
    /// makeElement() function.
    /// \param _tex The texture this element will use.
    /// \param _orient The edge of the screen this element will face.
    /// \return A pointer to the new element.
    Element *makeElement(SDL_Texture *_tex, const Orientation &_orient = BOTTOM);

    /// \brief Constructs a dynamically allocated element using the given parameters. This function lets you specify which part of the texture to use, as opposed to the other
    /// makeElement() function.
    /// \param _tex The texture this element will use.
    /// \param _orient The edge of the screen this element will face.
    /// \return A pointer to the new element.
    Element *makeElement(SDL_Texture *_tex, const SDL_Rect &_srcRect, const SDL_Rect &_destRect, const Orientation &_orient = BOTTOM);

    /// \brief Constructs a dynamically allocated card with the given parameters.
    /// \param _type The type of card to produce (its rank and suit).
    /// \param _orient The edge of the screen this card will face.
    /// \return A pointer to the new card.
    Card *makeCard(const PlayingCard &_type, const Orientation &_orient = BOTTOM);

    /// \brief Constructs a dynamically allocated label with the given parameters.
    /// \param _inputString The text on the label.
    /// \param _orient The edge of the screen this label will face.
    /// \param _lifetime The number of update() calls this label will last until it is marked for removal.
    /// \return A pointer to the new label.
    Label *makeLabel(const std::string &_inputString, const Orientation &_orient = BOTTOM, const int &_lifetime = 0);

private:
    const CardInfo* m_cardInfo;
    const LabelFormat* m_labelFormat;
};

}

#endif // ELEMENTMAKER_H
