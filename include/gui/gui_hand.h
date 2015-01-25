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
/// derived from or directly associated with either of them.
class Hand
{
public:
    /// \brief The hand constructor.
    /// \param _cards A vector containing all the cards in this hand.
    /// \param _orient The edge of the screen this hand should face. This *can* be different to the orientations of the cards themselves, but the hand will look rather odd.
    /// \return A Hand object.
    Hand(const std::vector<Card*> &_cards, const Orientation &_orient);

    /// \brief Adds a new card to the hand and adjusts the card positions accordingly.
    /// \param _inputCard A pointer to the GUI card to add - this should be created using DealerGUI::uniqueCard().
    void addCard(Card*_inputCard);

    /// \brief Sets the position of the group of cards instantly.
    /// \param _p The SDL point where the centre of the group should be.
    void setPos(const SDL_Point &_p);

    /// \brief Moves the group of cards with cosine interpolation to the specified point.
    /// \param _p The SDL point where the centre of the group should move to.
    void moveTo(const SDL_Point &_p);

    /// \brief Burns all the cards in the group.
    void burn();

    /// \brief Marks all the cards in the group for removal once they have reached their destination points.
    void kill();

    /// \brief Marks all the cards in the group for removal immediately.
    void killNow();

    /// \brief Turns all the cards in the group face-up or face-down.
    /// \param _isFlipped True for face-down, false for face-up.
    /// \param _instantly True to turn the cards instantly, false to animate the flipping of the cards.
    void setFlipped(const bool &_isFlipped, const bool &_instantly = false);

    /// \brief Returns the screenwise "height" of this hand i.e. the total number of pixels it takes up in the SCREEN's y direction, not its own.
    int getHeight();

    /// \brief Returns the screenwise "width" of this hand i.e. the total number of pixels it takes up in the SCREEN's x direction, not its own.
    int getWidth();

    /// \brief Moves the hand to the specified screen edge.
    /// \param _orient The screen edge to move to.
    /// \param _instantly True to move immediately, false to interpolate the position there over a number of update cycles.
    void align(const Orientation &_orient, const bool &_instantly = false);

    /// \brief Returns the point the hand would move to to align with the specified screen edge.
    /// \param _orient The edge of the screen the hand would move to.
    SDL_Point aligned(const Orientation &_orient);

private:
    std::vector<Card*> m_cards;
    Orientation m_orient;
    SDL_Point m_origin;
};

}

#endif // HAND_H
