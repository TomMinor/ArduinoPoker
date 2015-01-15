#ifndef ELEMENTMAKER_H
#define ELEMENTMAKER_H

#include <SDL.h>
#include "gui_element.h"
#include "gui_card.h"
#include "gui_label.h"

class GUI_ElementMaker
{
public:
    GUI_ElementMaker(const GUI_CardInfo* _cardInfo, const GUI_LabelFormat* _labelFormat);
    GUI_Card *makeCard(const PlayingCard &_type, const GUI_Orientation &_orient);
    GUI_Label *makeLabel(const std::string &_inputString, const GUI_Orientation &_orient, const int &_lifetime);

private:
    const GUI_CardInfo* m_cardInfo;
    const GUI_LabelFormat* m_labelFormat;
};

#endif // ELEMENTMAKER_H
