#ifndef ELEMENTMAKER_H
#define ELEMENTMAKER_H

#include <SDL.h>
#include "element.h"
#include "card.h"
#include "label.h"

class ElementMaker
{
public:
    ElementMaker();
    Card makeCard(CardInfo _info, Rank _rank, Suit _suit, Orientation _orient);
    Label makeLabel(LabelFormat _format, std::string _inputString, Orientation _orient);
};

#endif // ELEMENTMAKER_H
