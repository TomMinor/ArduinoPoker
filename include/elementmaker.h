#ifndef ELEMENTMAKER_H
#define ELEMENTMAKER_H

#include <SDL.h>
#include "element.h"
#include "card.h"
#include "label.h"

class ElementMaker
{
public:
    ElementMaker(const CardInfo* _cardInfo, const LabelFormat* _labelFormat);
    Card *makeCard(const CardType &_type, const Orientation &_orient);
    Label *makeLabel(const std::string &_inputString, const Orientation &_orient);

private:
    const CardInfo* m_cardInfo;
    const LabelFormat* m_labelFormat;
};

#endif // ELEMENTMAKER_H
