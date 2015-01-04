#include "dealer/pokerHands.h"
#include <iostream>
#include <vector>
#include <algorithm>

void hands::findSpareCards(const player &_player, const std::vector<PlayingCard> &_river, std::vector<PlayingCard> _spareCards)
{
    // Firstly put all remaining cards not in players best hand into a temporary vector spareCards.
    //std::vector<PlayingCard> spareCards;
    std::vector<PlayingCard>::iterator it;
    for (int i=0;i<2;i++)
    {
      it=std::find(_player.getHand().begin(),_player.getHand().end(),_player.getHoleCard(i));
      if(it==_player.getHand().end())
      {
        _spareCards.push_back(_player.getHoleCard(i));
      }
    }
    for (int i=0;i<5;i++)
    {
        it=std::find(_player.getHand().begin(),_player.getHand().end(),_river[i]);
        if(it==_player.getHand().end())
        {
          _spareCards.push_back(_river[i]);
        }
    }
    // All remaining cards now in tmp.

}

void hands::addHighestCard(player &_player, const std::vector<PlayingCard> &_river)
{
    // need to add tie breaker score, change if new score is higher.
    // Firstly put all remaining cards not in players best hand into a temporary vector tmp.
    std::vector<PlayingCard> spareCards;
    std::vector<PlayingCard>::iterator it;
    for (int i=0;i<2;i++)
    {
      it=std::find(_player.getHand().begin(),_player.getHand().end(),_player.getHoleCard(i));
      if(it==_player.getHand().end())
      {
        spareCards.push_back(_player.getHoleCard(i));
      }
    }

    for (int i=0;i<5;i++)
    {
        it=std::find(_player.getHand().begin(),_player.getHand().end(),_river[i]);
        if(it==_player.getHand().end())
        {
          spareCards.push_back(_river[i]);
        }
    }
    // All remaining cards now in tmp.

    //spareCards = findSpareCards(_player, _river, spareCards);
    //findSpareCards(_player, _river, spareCards);

    // Find the highest card in tmp and add to hand.
    _player.setHandCard(spareCards[0]);
    for (unsigned int i=1;i<spareCards.size();i++)
    {
        if (spareCards[i].getRank()>_player.getHandCard(_player.getNumCards()-1).getRank())
        {
            _player.popHandCard();
            _player.setHandCard(spareCards[i]);
        }
    }

}
//---------------------------------------------------------------------------------------------------------
//void hands::highestCard(player &_player)
//{
//    _player.setScore(_player.getHandCard(0).getRank());
//    for (int i=1;i<5;i++)
//    {
//      _player.setScore((_player.getHandCard(i).getRank()>_player.getHandCard(i-1).getRank()) ?
//                        _player.getHandCard(i).getRank():_player.getHandCard(i-1).getRank());
//    }
//}
//---------------------------------------------------------------------------------------------------------
void hands::highestCard(player &_player, const std::vector<PlayingCard> &_river)
{
    _player.setHandCard((_player.getHoleCard(1).getRank()>_player.getHoleCard(0).getRank())?
                         _player.getHoleCard(1):_player.getHoleCard(0));

    for (int i=0;i<5;i++)
    {
        if(_river[i].getRank()>_player.getHandCard(0).getRank())
        {
            _player.popHandCard();
            _player.setHandCard(_river[i]);
        }
    }
    _player.setScore(_player.getHandCard(0).getRank());

    for(int i=0;i<4;i++)
    {
        addHighestCard(_player,_river);
    }
    _player.setKicker(_player.getHandCard(1).getRank());
    std::cout<<"checking for high card\n";
}
//---------------------------------------------------------------------------------------------------------
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
    int scores[_numPlayers];
    int topScore;
    std::vector<int> winner;
    int kicker[_numPlayers];
    int topkicker;
    std::vector<int> tieWinner;


    // Find the highest score out of the players
    hands::bestHand(_livePlayers[0],_river);
    scores[0] = _livePlayers[0].getScore();
    topScore = scores[0];
    //topScore = _livePlayers[0].getScore();
    for (int i=1;i<_numPlayers;i++)
    {
        std::cout<<"----------next player----------\n";
        hands::bestHand(_livePlayers[i],_river);
        scores[i] = _livePlayers[i].getScore();
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
        //hands::highestCard(_livePlayers[winner[0]]);
        kicker[0] = _livePlayers[winner[0]].getKicker();
        topkicker = kicker[0];
        topkicker = _livePlayers[winner[0]].getKicker();
        for (unsigned int i=1; i<winner.size()+1; i++)
        {
            // use winner[i] to get player for highest card parameter.
            //hands::highestCard(_livePlayers[winner[i]]);
            kicker[i] = _livePlayers[i].getScore();
            topkicker = (kicker[i]>topkicker)?kicker[i]:topkicker;
            topkicker = (_livePlayers[i].getScore()>topkicker)?_livePlayers[i].getScore():topkicker;
        }

        for (unsigned int i=0;i<winner.size();i++)
        {
            if (_livePlayers[winner[i]].getScore() == topkicker)
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
    {   std::cout<<"winner is player "<<winner[0]<<"\n";
        std::cout<<"score of: "<<_livePlayers[winner[0]].getScore()<<"\n";
        std::cout<<"kicker of: "<<_livePlayers[winner[0]].getKicker()<<"\n";
        WINNERS.push_back(_livePlayers[winner[0]]);
    }


    std::cout<<"\n========================================================\n";
    std::cout<<"\tWinner Winner, Chicken Dinner!!!";
    std::cout<<"\n========================================================\n";
}
