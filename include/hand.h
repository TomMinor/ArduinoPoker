#ifndef HAND_H
#define HAND_H

#include "elementmaker.h"
#include <vector>

class Hand
{
public:
    Hand(const SDL_Point &_origin, const std::vector<Card *> &_cards, const Orientation &_orient);
    void moveTo(const SDL_Point &_p);
    void setFlipped(const bool &_isFlipped);
    void burn();
    void update();
    void draw();
private:
    std::vector<Card*> m_cards;
    Orientation m_orient;
};

#endif // HAND_H
