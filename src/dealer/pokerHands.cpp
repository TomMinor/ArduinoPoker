#include "dealer/pokerHands.h"
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<PlayingCard> hands::findSpareCards(const player &_player, const std::vector<PlayingCard> &_river)
{
    std::vector<PlayingCard> spareCards;
    bool cardInHand;

    // Find unsued cards in player Hole cards
    for (unsigned int i=0;i<_player.getHole().size();i++)
    {
      cardInHand = false;
      for(unsigned int j=0;j<_player.getHand().size();j++)
      {
          if(_player.getHoleCard(i)==_player.getHandCard(j))
          {cardInHand = true;}
      }
      if(!cardInHand)
      {spareCards.push_back(_player.getHoleCard(i));}
    }

    // Find unsued cards in river cards
    for (unsigned int i=0;i<_river.size();i++)
    {
      cardInHand = false;
      for(unsigned int j=0;j<_player.getHand().size();j++)
      {
          if(_river[i]==_player.getHandCard(j))
          {cardInHand = true;}
      }
      if(!cardInHand)
      {spareCards.push_back(_river[i]);}
    }

    return spareCards;
}

bool hands::lowToHigh(const PlayingCard &_a,const PlayingCard &_b)
{
    return (_a.getRank()<_b.getRank());
}

bool hands::highToLow(const PlayingCard &_a, const PlayingCard &_b)
{
    return (_a.getRank()>_b.getRank());
}

void hands::addHighestCard(player &_player, const std::vector<PlayingCard> &_river)
{
    std::vector<PlayingCard> spareCards;
    spareCards=findSpareCards(_player,_river);

    // Find the highest card in spareCards and add to hand.
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

void hands::findPair(player &_player, const std::vector<PlayingCard> &_river)
{
    bool pairFound = false;
    unsigned int origHandSize = _player.getHand().size();
    std::vector<PlayingCard> spareCards;
    spareCards = findSpareCards(_player,_river);
    std::sort(spareCards.begin(),spareCards.end(),highToLow);

    // Find pairs and push them into players hand.
    for(unsigned int i=0;i<spareCards.size()-1;i++)
    {
        for(unsigned int j=i+1;j<spareCards.size();j++)
        {
            if(spareCards[i].getRank()==spareCards[j].getRank())
            {
                pairFound = true;
                _player.setHandCard(spareCards[i]);
                _player.setHandCard(spareCards[j]);
            }
        }
    }

    // Only keep the first and hence largest pair found
    while(_player.getHand().size()>origHandSize+2)
    {
        _player.popHandCard();
    }

    // Set score if pair found
    if(pairFound)
    {
        _player.setScore(_player.getHandCard(origHandSize).getRank());
    }
    else{_player.setScore(0);}
}

void hands::fillHand(player &_player, const std::vector<PlayingCard> &_river)
{
    unsigned int kickerID = _player.getHand().size();
    for(unsigned int i=0;i<5-_player.getHand().size();i++)
    {
        addHighestCard(_player,_river);
    }
    _player.setKicker(_player.getHandCard(kickerID).getRank());
}

//---------------------------------------------------------------------------------------------------------
void hands::highestCard(player &_player)
{
    _player.setKicker(_player.getHandCard(0).getRank());
    for (unsigned int i=1;i<_player.getHand().size();i++)
    {
      if(_player.getHandCard(i).getRank()>_player.getKicker())
      {
          _player.setKicker(_player.getHandCard(i).getRank());
      }
    }
}
//---------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------
void hands::highestCard(player &_player, const std::vector<PlayingCard> &_river)
{
    std::cout<<"checking for high card\n";

    _player.setHandCard((_player.getHoleCard(1).getRank()>_player.getHoleCard(0).getRank())?
                         _player.getHoleCard(1):_player.getHoleCard(0));

    for (unsigned int i=0;i<_river.size();i++)
    {
        if(_river[i].getRank()>_player.getHandCard(0).getRank())
        {
            _player.popHandCard();
            _player.setHandCard(_river[i]);
        }
    }
    _player.setScore(_player.getHandCard(0).getRank());

    fillHand(_player,_river);

}
//---------------------------------------------------------------------------------------------------------

void hands::pairs(player &_player, const std::vector<PlayingCard> &_river)
{
    std::cout<<"checking for two pair\n";

    //(((B-3)*(B-2))/2)+S-1 + 26(max 1Pair) = score!!

    findPair(_player,_river);
    int majorS = _player.getScore();
    if(majorS > 0)
    {
        std::cout<<majorS<<", ";
        findPair(_player,_river);
        int minorS = _player.getScore();
        if(minorS>0)
        {
            std::cout<<majorS<<"\n";
            fillHand(_player,_river);
            int finalScore = (((majorS-2)*(majorS-1))/2)+ (minorS) + 26;
            _player.setScore(finalScore);
        }
        else
        {   // Must pop off the first pair
            _player.setScore(13+majorS);
            fillHand(_player,_river);
        }

    }

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

    hands::pairs(_player, _river);
    if (_player.getScore()>0)
      return;

    hands::highestCard(_player, _river);
    if (_player.getScore()>0)
      return;

}

void hands::winner(std::vector<player> &_livePlayers, const std::vector<PlayingCard> &_river)
{
    unsigned int numPlayers = _livePlayers.size();

    int topScore;
    std::vector<int> winner;
    int topkicker;
    std::vector<int> tieWinner;
    std::vector<player> WINNERS;

    // Find the highest score out of the players
    hands::bestHand(_livePlayers[0],_river);
    topScore = _livePlayers[0].getScore();
    for (unsigned int i=1;i<numPlayers;i++)
    {
        hands::bestHand(_livePlayers[i],_river);
        topScore = (_livePlayers[i].getScore()>topScore)?
                    _livePlayers[i].getScore():topScore;
    }

    // Record player ID's that have top score
    for (unsigned int i=0;i<numPlayers;i++)
    {
        if (_livePlayers[i].getScore()==topScore)
        {   winner.push_back(i);    }
    }

    if (winner.size()>1)
    {
        // More than one player has the high score,
        // Now need to check these players Kicker,
        topkicker = _livePlayers[winner[0]].getKicker();
        for (unsigned int i=1; i<winner.size(); i++)
        {
            // use winner[i] to get playerID for highest card parameter.
            topkicker = (_livePlayers[i].getKicker()>topkicker)?
                         _livePlayers[i].getKicker():topkicker;
        }

        for (unsigned int i=0;i<winner.size();i++)
        {   //tieWinner contains ID of players with highest card
            if (_livePlayers[winner[i]].getKicker() == topkicker)
            {   tieWinner.push_back(winner[i]);  }
        }
        std::cout<<"There are "<<tieWinner.size()<<" winners\n";
        for (unsigned int i=0;i<tieWinner.size();i++)
        {
            std::cout<<tieWinner[i]<<" ";
            std::cout<<"score of: "<<_livePlayers[tieWinner[i]].getScore()<<"\n";
            std::cout<<"kicker of: "<<_livePlayers[tieWinner[i]].getKicker()<<"\n";
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
