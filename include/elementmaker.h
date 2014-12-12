#ifndef ELEMENTMAKER_H
#define ELEMENTMAKER_H

#include <SDL.h>
#include "element.h"
#include "card.h"
#include "label.h"

class ElementMaker
{
public:
<<<<<<< HEAD
    ElementMaker(const CardInfo* _cardInfo, const LabelFormat* _labelFormat);
    Card *makeCard(const CardType &_type, const Orientation &_orient);
    Label *makeLabel(const std::string &_inputString, const Orientation &_orient);

private:
    const CardInfo* m_cardInfo;
    const LabelFormat* m_labelFormat;
=======
    ElementMaker();
    Card makeCard(CardInfo _info, Rank _rank, Suit _suit, Orientation _orient);
    Label makeLabel(LabelFormat _format, std::string _inputString, Orientation _orient);
>>>>>>> 9a857e697db5c34734e45771dbf4daa043b18f26
};

#endif // ELEMENTMAKER_H
