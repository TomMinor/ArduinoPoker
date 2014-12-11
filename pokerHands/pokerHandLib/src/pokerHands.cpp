#include "pokerHands.h"
#include <iostream>
#include <vector>

void hands::highestCard(player &_player, const std::vector<card> &_river)
{
    // Only need to check players private cards
    std::cout<<"checking for high card\n";
    return;
}

void hands::pair(player &_player, const std::vector<card> &_river)
{
    std::cout<<"checking for pair\n";
    return;
}

void hands::twoPair(player &_player, const std::vector<card> &_river)
{
    std::cout<<"checking for two pair\n";
    return;
}

void hands::three(player &_player, const std::vector<card> &_river)
{
    std::cout<<"checking for three of a kind\n";
    return;
}

void hands::straight(player &_player, const std::vector<card> &_river)
{
    std::cout<<"checking for straight\n";
    return;
}

void hands::flush(player &_player, const std::vector<card> &_river)
{
    std::cout<<"checking for flush\n";
    return;
}

void hands::four(player &_player, const std::vector<card> &_river)
{
    std::cout<<"checking for four of a kind\n";
    return;
}
void hands::fullHouse(player &_player, const std::vector<card> &_river)
{
    std::cout<<"checking for full house\n";
    return;
}

void hands::straightFlush(player &_player, const std::vector<card> &_river)
{
    std::cout<<"checking for straight flush\n";
    return;
}
//-----------------------------------------------------------------------------
void hands::bestHand(player &_player, const std::vector<card> &_river)
{
    hands::straightFlush(_player, _river);
    if (_player.getScore()>0)
      return;

    hands::four(_player, _river);
    if (_player.getScore()>0)
      return;

    hands::fullHouse(_player, _river);
    if (_player.getScore()>0)
      return;

    hands::flush(_player, _river);
    if (_player.getScore()>0)
      return;

    hands::straight(_player, _river);
    if (_player.getScore()>0)
      return;

    hands::three(_player, _river);
    if (_player.getScore()>0)
      return;

    hands::twoPair(_player, _river);
    if (_player.getScore()>0)
      return;

    hands::pair(_player, _river);
    if (_player.getScore()>0)
      return;

    hands::highestCard(_player, _river);
    if (_player.getScore()>0)
      return;

}

void hands::winner(const int &_numPlayers, std::vector<player> &_livePlayers, const std::vector<card> &_river)
{
    int scores[_numPlayers];
    int topScore;
    std::vector<int> winner;
    //int tieBreaker[_numPlayers];
    int tieBreakerScore[_numPlayers];
    int topTieBreakerScore;
    std::vector<int> tieWinner;


    // Find the highest score out of the players
    hands::bestHand(_livePlayers[0],_river);
    scores[0] = _livePlayers[0].m_score;
    topScore = scores[0];
    for (int i=1;i<_numPlayers;i++)
    {
        std::cout<<"----------next player----------\n";
        hands::bestHand(_livePlayers[i],_river);
        scores[1] = _livePlayers[i].getScore();
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
        hands::highestCard(_livePlayers[winner[0]],_river);
        tieBreakerScore[0] = _livePlayers[winner[0]].getScore();
        topTieBreakerScore = tieBreakerScore[0];
        for (unsigned int i=1;i<winner.size();i++)
        {
            // use winner[i] to get player cards for highest card parameter.
            hands::highestCard(_livePlayers[winner[i]],_river);
            tieBreakerScore[i] = _livePlayers[i].getScore();
            topTieBreakerScore = (tieBreakerScore[i]>topTieBreakerScore)?tieBreakerScore[i]:topTieBreakerScore;
        }

        for (unsigned int i=1;i<winner.size();i++)
        {
            if (tieBreakerScore[i] == topTieBreakerScore)
            {
                tieWinner.push_back(winner[i]);
            }
        }
        std::cout<<"There are "<<tieWinner.size()<<"winners\n";
        for (unsigned int i=0;i<tieWinner.size();i++)
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
