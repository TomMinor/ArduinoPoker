#ifndef HAND_H
#define HAND_H

#include "gui_elementmaker.h"
#include <vector>

//This class is simply for easy manipulation of a number of cards at once.
//It should be obtained using DealerGUI::UniqueHand() to ensure all the cards are updated and destroyed properly.
//NOTE: Currently, only the BOTTOM orientation works properly.
class GUI_Hand
{
public:
    GUI_Hand(const std::vector<GUI_Card*> &_cards, const GUI_Orientation &_orient);
    void setPos(const SDL_Point &_p);
    void moveTo(const SDL_Point &_p);
    void burn();
    void kill();
    void setFlipped(const bool &_isFlipped);
    int getHeight();
    int getWidth();
    SDL_Point aligned(const GUI_Orientation &_orient);
private:
    std::vector<GUI_Card*> m_cards;
    GUI_Orientation m_orient;
    SDL_Point m_origin;
};

#endif // HAND_H
