#include "pokerHands.h"
#include <iostream>
#include <vector>

int hands::highestCard()
{
    // Only need to check players private cards
    int score = 0;
    std::cout<<"checking for high card\n";
    return score;
}

int hands::pair()
{
    int score = 0;
    std::cout<<"checking for pair\n";
    return score;
}

int hands::twoPair()
{
    int score = 0;
    std::cout<<"checking for two pair\n";
    return score;
}

int hands::three()
{
    int score = 0;
    std::cout<<"checking for three of a kind\n";
    return score;
}

int hands::straight()
{
    int score = 0;
    std::cout<<"checking for straight\n";
    return score;
}

int hands::flush()
{
    int score = 0;
    std::cout<<"checking for flush\n";
    return score;
}

int hands::four()
{
    int score = 0;
    std::cout<<"checking for four of a kind\n";
    return score;
}
int hands::fullHouse()
{
    int score = 0;
    std::cout<<"checking for full house\n";
    return score;
}

int hands::straightFlush()
{
    int score = 0;
    std::cout<<"checking for straight flush\n";
    return score;
}
//-----------------------------------------------------------------------------
int hands::bestHand(const card _player1,const card _player2,const card _public[5])
{
    int score = 0;

    score = straightFlush();
    if (score==0)
    {
        score = fullHouse();
        if (score==0)
        {
            score = four();
            if (score==0)
            {
                score = flush();
                if (score==0)
                {
                    score = straight();
                    if (score==0)
                    {
                        score = three();
                        if (score==0)
                        {
                            score = twoPair();
                            if (score==0)
                            {
                                score = pair();
                                if (score==0)
                                {
                                    score = highestCard();
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return score;
}

void hands::winner(const int &_numPlayers, const card _players[], const card _public[5])
{
    int scores[_numPlayers];
    int topScore;
    std::vector<int> winner;
    int tieBreaker[_numPlayers];
    int tieBreakerScore;
    std::vector<int> tieWinner;


    // Find the highest score out of the players
    scores[0] = hands::bestHand(_players[0],_players[1],_public);
    topScore = scores[0];
    for (int i=1;i<_numPlayers;i++)
    {
        std::cout<<"----------next player----------\n";
        scores[i] = hands::bestHand(_players[2*i],_players[2*i+1],_public);
        topScore = (scores[i]>topScore)?scores[i]:topScore;
    }

    // Check how many players had the high score
    for (int i=0;i<_numPlayers;i++)
    {
        if (scores[i]==topScore)
        {
            // record which player had top score
            winner.push_back(i);
        }
    }

    //Find the player with the high score
    if (winner.size()>1)
    {
        // More than one player has the high score,
        // Now need to check these players highest card,
        // Note: only need to check their private cards.
        tieBreaker[0] = hands::highestCard();
        tieBreakerScore = tieBreaker[0];
        for (int i=1;i<winner.size();i++)
        {
            // use winner[i] to get player cards for highest card parameter.
            tieBreaker[i] = hands::highestCard();
            tieBreakerScore = (tieBreaker[i]>tieBreakerScore)?tieBreaker[i]:tieBreakerScore;
        }

        for (int i=1;i<winner.size();i++)
        {
            if (tieBreaker[i] == tieBreakerScore)
            {
                tieWinner.push_back(winner[i]);
            }
        }
        std::cout<<"There are "<<tieWinner.size()<<"winners\n";
        for (int i=0;i<tieWinner.size();i++)
        {
            std::cout<<tieWinner[i]<<", ";
        }
    }
    else {std::cout<<"winner is player "<<winner[0];}


    int a=10;
    int b=10;
    int c = (a==b)?1:2;
    std::cout<<c;

    std::cout<<"\n========================================================\n";
    std::cout<<"\tWinner Winner, Chicken Dinner!!!";
    std::cout<<"\n========================================================\n";
}
