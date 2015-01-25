#ifndef HAND_H
#define HAND_H

#include "gui_elementmaker.h"
#include <vector>

namespace GUI
{

/// \brief This class is simply for easy manipulation of a number of cards at once. Despite the name, it does not necessarily refer to the cards a player is holding.
///
/// It should be obtained using DealerGUI::UniqueHand() to ensure all the cards are updated and destroyed properly.
/// NOTE: Although this class contains many functions with the same names as the Card and Element classes, this is simply for consistency and convenience; it is not
/// derived from either of them.
/// NOTE: Currently, only the BOTTOM orientation works properly.
class Hand
{
public:
    /// \brief The hand constructor.
    /// \param _cards A vector containing all the cards in this hand.
    /// \param _orient
    Hand(const std::vector<Card*> &_cards, const Orientation &_orient);
    void addCard(Card*_inputCard);
    void setPos(const SDL_Point &_p);
    void moveTo(const SDL_Point &_p);
    void burn();
    void kill();
    void setFlipped(const bool &_isFlipped, const bool &_instantly = false);
    int getHeight();
    int getWidth();
    void align(const Orientation &_orient, const bool &_instantly = false);
    SDL_Point aligned(const Orientation &_orient);

private:
    std::vector<Card*> m_cards;
    Orientation m_orient;
    SDL_Point m_origin;
};

}

#endif // HAND_H
