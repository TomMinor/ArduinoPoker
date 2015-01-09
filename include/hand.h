#ifndef HAND_H
#define HAND_H

#include "elementmaker.h"
#include <vector>

//This class is simply for easy manipulation of a number of cards at once.
//It should be obtained using DealerGUI::UniqueHand() to ensure all the cards are updated and destroyed properly.
class Hand
{
public:
    Hand(const std::vector<Card*> &_cards, const Orientation &_orient);
    void setPos(const SDL_Point &_p);
    void moveTo(const SDL_Point &_p);
    void burn();
    void kill();
    void setFlipped(const bool &_isFlipped);
    unsigned int getHeight();
    unsigned int getWidth();
    SDL_Point aligned(const Orientation &_orient);
private:
    std::vector<Card*> m_cards;
    Orientation m_orient;
    SDL_Point m_origin;
};

#endif // HAND_H
