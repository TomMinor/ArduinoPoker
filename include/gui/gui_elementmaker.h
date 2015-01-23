#ifndef ELEMENTMAKER_H
#define ELEMENTMAKER_H

#include <SDL.h>
#include "gui_element.h"
#include "gui_card.h"
#include "gui_label.h"

namespace GUI
{

/// \brief This class serves as a factory for visual elements.
///
/// This layer of abstraction is needed because each type of visual element should ideally have a specialised constructor, but they are derived from the same class and
/// C++ does not support virtual constructors.
class ElementMaker
{
public:
    ElementMaker(const CardInfo* _cardInfo, const LabelFormat* _labelFormat);
    Element *makeElement(SDL_Texture *_tex, const Orientation &_orient = BOTTOM);
    Card *makeCard(const PlayingCard &_type, const Orientation &_orient = BOTTOM);
    Label *makeLabel(const std::string &_inputString, const Orientation &_orient = BOTTOM, const int &_lifetime = 0);

private:
    const CardInfo* m_cardInfo;
    const LabelFormat* m_labelFormat;
};

}

#endif // ELEMENTMAKER_H
