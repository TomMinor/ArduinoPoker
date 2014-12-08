#ifndef _POKERHANDS__H_
#define _POKERHANDS__H_

typedef struct CARDS
{
    int num;
    enum suit {spade, club, heart, diamond};
}card;

namespace hands
{
//-----------------------------------------------------------------------------------------------------------------------------
    // Evaluate hands methods
//-----------------------------------------------------------------------------------------------------------------------------
    int highestCard();      // SCORE 1-13    | 13 different valued high cards per suit, Ace is the highest.
    int pair();             // SCORE 14-26   | 13 different valued pairs, Ace,Ace being the higest.
    int twoPair();          // SCORE 27-104  | 78 different valued 2 pairs, Ace,Ace,King,King being the highest.
    int three();            // SCORE 105-117 | 13 different valued 3 of a Kinds, Ace,Ace,Ace being the highest.
    int straight();         // SCORE 118-127 | 10 different valued straights, 10-Ace being the highest valued.
    int flush();            // SCORE 128-140 | 13 different valued flushes, containing Ace being the highest value
    int fullHouse();        // SCORE 141-296 | 156 different valued full houses(13x12), Ace,Ace,Ace,King,King being the highest.
    int four();             // SCORE 297-309 | 13 different valued 4 of a kinds, Ace,Ace,Ace,Ace being the highest.
    int straightFlush();    // SCORE 310-319 | 10 different valued straight flushes, 10-Ace being the highest.
//-----------------------------------------------------------------------------------------------------------------------------
    // Decide winner methods
//-----------------------------------------------------------------------------------------------------------------------------
    int bestHand(const card _player1, const card _player2, const card _public[5]);
    void winner(const int &_numPlayers, const card _players[], const card _public[5]);
}

#endif
