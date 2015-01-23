#ifndef _POKERHANDS__H_
#define _POKERHANDS__H_

#include <vector>
#include "playingcard.h"
#include "player.h"
#include "cardStack.h"

/// @author Idris Miles
/// @version 1.0
/// @date 16/01/2015


/// @namespace hands encapsulates all methods used to find players best hand and ecide winner of Poker.
namespace hands
{
//-----------------------------------------------------------------------------------------------------------------------------
    // Evaluate hands methods
//-----------------------------------------------------------------------------------------------------------------------------
    /// @brief method to find spare cards not already being used in players hand
    /// @param [in] const Player
    /// @param [in] const cardStack
    /// @return [out] cardStack
    cardStack findSpareCards(const player &_player, const cardStack &_river);

    /// @brief method to add highest spare card into players hand.
    /// @param [in] player
    /// @param [in] const cardSack
    void addHighestCard(player &_player, const cardStack &_river);   // Used to add high cards to hand to complete hand, Does not effect score.

    /// @brief method to find highest pair in spare cards and add to player hand.
    /// @param [in] player
    /// @param [in] const cardSack
    void findPair(player &_player, const cardStack &_river);         // Finds highest pair in spare cards.

    /// @brief method to fill players hand (5 cards) with highest spare cards.
    /// @param [in] player
    /// @param [in] const cardSack
    void fillHand(player &_player, const cardStack &_river);         // Fills the rest of the hand and sets m_kicker

    /// @brief method to check if the straight in the players hand is also a flush,
    /// or if a flush can be made with the spare cards and maintain a straight.
    /// @param [in] player
    /// @param [in] const cardSack
    /// @return [out] bool
    bool checkStraightHasFlush(player &_player, const cardStack &_river, const Suit::Value _suit, unsigned int _numSuit);
//-----------------------------------------------------------------------------------------------------------------------------

    /// @brief method to find highest card and add to players hand until it is full,
    /// and updates m_score and m_kicker.
    void highestCard(player &_player, const cardStack &_river);      // SCORE 1-13    | 13 different valued high cards per suit, Ace is the highest.

    /// @brief method to add highest pairs to players hand until it is full,
    /// add highest spare cards to fill hand and update m_score and m_kicker.
    /// @param [in] player
    /// @param [in] const cardSack
    void pairs(player &_player, const cardStack &_river);            // SCORE 14-26   | 13 different valued pairs, Ace,Ace being the higest.
                                                                     // SCORE 27-104  | 78 different valued 2 pairs, Ace,Ace,King,King being the highest.

    /// @brief method to add highest three of a kind to players hand,
    /// add highest spare cards to fill hand and update m_score and m_kicker.
    /// @param [in] player
    /// @param [in] const cardSack
    void three(player &_player, const cardStack &_river);            // SCORE 105-117 | 13 different valued 3 of a Kinds, Ace,Ace,Ace being the highest.

    /// @brief method to add highest straight to players hand,
    /// and update m_score, note m_kicker is zero.
    /// @param [in] player
    /// @param [in] const cardSack
    void straight(player &_player, const cardStack &_river);         // SCORE 118-127 | 10 different valued straights, 10-Ace being the highest valued.

    /// @brief method to add highest flush to players hand,
    /// and update m_score, note m_kicker is zero.
    /// @param [in] player
    /// @param [in] const cardSack
    void flush(player &_player, const cardStack &_river);            // SCORE 128-140 | 13 different valued flushes, containing Ace being the highest value

    /// @brief method to add highest three of a kind and highest pair to players hand,
    /// and update m_score, note m_kicker is zero.
    /// @param [in] player
    /// @param [in] const cardSack
    void fullHouse(player &_player, const cardStack &_river);        // SCORE 141-296 | 156 different valued full houses(13x12), Ace,Ace,Ace,King,King being the highest.

    /// @brief method to add highest four of a kind to players hand,
    /// add highest spare cards to fill hand and update m_score and m_kicker.
    /// @param [in] player
    /// @param [in] const cardSack
    void four(player &_player, const cardStack &_river);             // SCORE 297-309 | 13 different valued 4 of a kinds, Ace,Ace,Ace,Ace being the highest.

    /// @brief method to add highest straight flush to players hand,
    /// and update m_score, note m_kicker is zero.
    /// @param [in] player
    /// @param [in] const cardSack
    void straightFlush(player &_player, const cardStack &_river);    // SCORE 310-319 | 10 different valued straight flushes, 10-Ace being the highest.
//-----------------------------------------------------------------------------------------------------------------------------
    // Decide winner methods
//-----------------------------------------------------------------------------------------------------------------------------

    /// @brief method to add best hand to player,
    /// and update m_score and m_kicker.
    /// @param [in] player
    /// @param [in] const cardSack
    void bestHand(player &_player, const cardStack &_river);

    /// @brief method to find player ID's of players with higest m_kicker,
    /// in the event of m_score being the same in players.
    /// @param [in] std::vector<player>
    /// @param [in] const std::vector<int>
    std::vector<player> tieBreak(std::vector<player> &_livePlayers, const std::vector<int> _ID);

    /// @brief method to find the players with the best hand and score.
    /// @param [in] std::vector<player>
    /// @param [in] const cardSack
    /// @return std::vector<player>
    std::vector<player> winner(std::vector<player> &_livePlayers, const cardStack &_river);

}

#endif
