#include "dealer/pokerHands.h"
#include <iostream>
#include <vector>
#include <algorithm>


void hands::addHighestCard(player &_player, const std::vector<PlayingCard> &_river)
{
    // need to add tie breaker score, change if new score is higher.
    std::vector<PlayingCard> tmpCards;
    std::vector<PlayingCard>::iterator it;
    for (int i=0;i<2;i++)
    {
      it=std::find(_player.getHand().begin(),_player.getHand().end(),_player.getCard(i));
      if(it==_player.getHand().end())
      {
        tmpCards.push_back(_player.getCard(i));
      }
    }
    for (int i=0;i<5;i++)
    {
        it=std::find(_player.getHand().begin(),_player.getHand().end(),_river[i]);
        if(it==_player.getHand().end())
        {
          tmpCards.push_back(_river[i]);
        }
    }

    _player.setHandCard(tmpCards[0]);
    for (int i=1;i<tmpCards.size();i++)
    {
        if (tmpCards[i].getRank()>tmpCards[i-1].getRank())
        {
            _player.popHandCard();
            _player.setHandCard(tmpCards[i]);
        }
    }

}

void hands::highestCard(player &_player)
{
    _player.setScore(_player.getHandCard(0).getRank());
    for (int i=1;i<5;i++)
    {
      _player.setScore((_player.getHandCard(i).getRank()>_player.getHandCard(i-1).getRank()) ?
                        _player.getHandCard(i).getRank():_player.getHandCard(i-1).getRank());
    }
}

void hands::highestCard(player &_player, const std::vector<PlayingCard> &_river)
{
    _player.setHandCard((_player.getCard(0).getRank()>_player.getCard(1).getRank())?
                         _player.getCard(0):_player.getCard(1));

    for (int i=0;i<5;i++)
    {
        if(_river[i].getRank()>_player.getHandCard(0).getRank())
        {
            _player.setHandCard(_river[i]);
        }
    }

    std::cout<<"checking for high card\n";
}

void hands::pair(player &_player, const std::vector<PlayingCard> &_river)
{
    std::cout<<"checking for pair\n";
}

void hands::twoPair(player &_player, const std::vector<PlayingCard> &_river)
{
    std::cout<<"checking for two pair\n";
}

void hands::three(player &_player, const std::vector<PlayingCard> &_river)
{
    std::cout<<"checking for three of a kind\n";
}

void hands::straight(player &_player, const std::vector<PlayingCard> &_river)
{
    std::cout<<"checking for straight\n";
}

void hands::flush(player &_player, const std::vector<PlayingCard> &_river)
{
    std::cout<<"checking for flush\n";
}

void hands::four(player &_player, const std::vector<PlayingCard> &_river)
{
    std::cout<<"checking for four of a kind\n";;
}
void hands::fullHouse(player &_player, const std::vector<PlayingCard> &_river)
{
    std::cout<<"checking for full house\n";
}

void hands::straightFlush(player &_player, const std::vector<PlayingCard> &_river)
{
    std::cout<<"checking for straight flush\n";
}
//-----------------------------------------------------------------------------
void hands::bestHand(player &_player, const std::vector<PlayingCard> &_river)
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

void hands::winner(const int &_numPlayers, std::vector<player> &_livePlayers, const std::vector<PlayingCard> &_river)
{
    std::vector<player> WINNERS;
    int numPlayers = _livePlayers.size();
    int scores[_numPlayers];
    int topScore;
    std::vector<int> winner;
    int tieBreakerScore[_numPlayers];
    int topTieBreakerScore;
    std::vector<int> tieWinner;


    // Find the highest score out of the players
    hands::bestHand(_livePlayers[0],_river);
    scores[0] = _livePlayers[0].getScore();
    topScore = scores[0];
    topScore = _livePlayers[0].getScore();
    for (int i=1;i<_numPlayers;i++)
    {
        std::cout<<"----------next player----------\n";
        hands::bestHand(_livePlayers[i],_river);
        scores[1] = _livePlayers[i].getScore();
        topScore = (scores[i]>topScore)?scores[i]:topScore;
        topScore = (_livePlayers[i].getScore()>topScore)?_livePlayers[i].getScore():topScore;
    }

    // Check how many players had the high score
    for (int i=0;i<_numPlayers;i++)
    {
        if (_livePlayers[i].getScore()==topScore)
        {
            // record player ID that had top score
            winner.push_back(i);
        }
    }

    //Find the player with the high score
    if (winner.size()>1)
    {
        // More than one player has the high score,
        // Now need to check these players highest card,
        // Note: only need to check their private cards.
        hands::highestCard(_livePlayers[winner[0]]);
        tieBreakerScore[0] = _livePlayers[winner[0]].getScore();
        topTieBreakerScore = tieBreakerScore[0];
        topTieBreakerScore = _livePlayers[winner[0]].getScore();
        for (unsigned int i=1; i<winner.size()+1; i++)
        {
            // use winner[i] to get player for highest card parameter.
            hands::highestCard(_livePlayers[winner[i]]);
            tieBreakerScore[i] = _livePlayers[i].getScore();
            topTieBreakerScore = (tieBreakerScore[i]>topTieBreakerScore)?tieBreakerScore[i]:topTieBreakerScore;
            topTieBreakerScore = (_livePlayers[i].getScore()>topTieBreakerScore)?_livePlayers[i].getScore():topTieBreakerScore;
        }

        for (unsigned int i=0;i<winner.size();i++)
        {
            if (_livePlayers[winner[i]].getScore() == topTieBreakerScore)
            {
                //tieWinner contains ID of players with highest card
                tieWinner.push_back(winner[i]);
            }
        }
        std::cout<<"There are "<<tieWinner.size()<<"winners\n";
        for (unsigned int i=0;i<tieWinner.size();i++)
        {
            std::cout<<tieWinner[i]<<" ";
            WINNERS.push_back(_livePlayers[tieWinner[i]]);
        }
    }
    else
    {   std::cout<<"winner is player "<<winner[0];
        WINNERS.push_back(_livePlayers[winner[0]]);
    }


    std::cout<<"\n========================================================\n";
    std::cout<<"\tWinner Winner, Chicken Dinner!!!";
    std::cout<<"\n========================================================\n";
}
