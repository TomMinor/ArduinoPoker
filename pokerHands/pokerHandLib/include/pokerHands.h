#ifndef _POKERHANDS__H_
#define _POKERHANDS__H_

#include <vector>
#include "card.h"
#include "player.h"


namespace hands
{
//-----------------------------------------------------------------------------------------------------------------------------
    // Evaluate hands methods
//-----------------------------------------------------------------------------------------------------------------------------
    void highestCard(player &_player);
    void highestCard(player &_player, const std::vector<card> &_river);      // SCORE 1-13    | 13 different valued high cards per suit, Ace is the highest.
    void pair(player &_player, const std::vector<card> &_river);             // SCORE 14-26   | 13 different valued pairs, Ace,Ace being the higest.
    void twoPair(player &_player, const std::vector<card> &_river);          // SCORE 27-104  | 78 different valued 2 pairs, Ace,Ace,King,King being the highest.
    void three(player &_player, const std::vector<card> &_river);            // SCORE 105-117 | 13 different valued 3 of a Kinds, Ace,Ace,Ace being the highest.
    void straight(player &_player, const std::vector<card> &_river);         // SCORE 118-127 | 10 different valued straights, 10-Ace being the highest valued.
    void flush(player &_player, const std::vector<card> &_river);            // SCORE 128-140 | 13 different valued flushes, containing Ace being the highest value
    void fullHouse(player &_player, const std::vector<card> &_river);        // SCORE 141-296 | 156 different valued full houses(13x12), Ace,Ace,Ace,King,King being the highest.
    void four(player &_player, const std::vector<card> &_river);             // SCORE 297-309 | 13 different valued 4 of a kinds, Ace,Ace,Ace,Ace being the highest.
    void straightFlush(player &_player, const std::vector<card> &_river);    // SCORE 310-319 | 10 different valued straight flushes, 10-Ace being the highest.
//-----------------------------------------------------------------------------------------------------------------------------
    // Decide winner methods
//-----------------------------------------------------------------------------------------------------------------------------
    void bestHand(player &_player, const std::vector<card> &_river);
    void winner(const int &_numPlayers, std::vector<player> &_livePlayers, const std::vector<card> &_river);
    //int * winner(const int &_numPlayers, std::vector<player> &_livePlayers, const std::vector<card> &_river);
}

#endif
