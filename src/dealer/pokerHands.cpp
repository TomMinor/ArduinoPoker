#include "dealer/pokerHands.h"
#include <iostream>
#include <vector>
#include <algorithm>

//--------------------------------------------------------------------------------------
cardStack hands::findSpareCards( const player &_player, const cardStack &_river)
{
    cardStack spareCards;
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
      {spareCards.addCard(_player.getHoleCard(i));}
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
      {spareCards.addCard(_river[i]);}
    }

    return spareCards;
}


//--------------------------------------------------------------------------------------
void hands::addHighestCard(player &_player, const cardStack &_river)
{
    cardStack spareCards;
    spareCards=findSpareCards(_player,_river);
    _player.setHandCard(spareCards.getHighestCard());
}

//--------------------------------------------------------------------------------------
void hands::findPair(player &_player, const cardStack &_river)
{
    if(_player.getHand().size() >3)
    {
        return;
    }

    bool pairFound = false;
    unsigned int origHandSize = _player.getHand().size();
    cardStack spareCards;
    spareCards = findSpareCards(_player,_river);
    spareCards.sort();

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
        _player.removeLastHandCard();
    }

    // Set score if pair found
    if(pairFound)
    {
        _player.setScore(_player.getHandCard(origHandSize).getRank());
    }
    else{_player.setScore(0);}
}

//--------------------------------------------------------------------------------------
void hands::fillHand(player &_player, const cardStack &_river)
{
    unsigned int kickerID = _player.getHand().size();
    while(_player.getHand().size() < 5)
    {
        addHighestCard(_player,_river);
    }

    _player.setKicker(_player.getHandCard(kickerID).getRank());
}


//--------------------------------------------------------------------------------------
  //========== Hands ===========
//--------------------------------------------------------------------------------------
void hands::highestCard(player &_player, const cardStack &_river)
{
    cardStack spareCards;
    // Find spare cards and sort
    spareCards=findSpareCards(_player,_river);
    spareCards.sort();

    // Add highest card to players hand
    _player.setHandCard(spareCards[0]);
    _player.setScore(_player.getHandCard(0).getRank());

    // Fill players hand with remaining high cards.
    fillHand(_player,_river);

}

//--------------------------------------------------------------------------------------
void hands::pairs(player &_player, const cardStack &_river)
{
    findPair(_player,_river);
    int majorS = _player.getScore();
    if(majorS > 0)
    {  // First pair found
        _player.setScore(0);
        findPair(_player,_river);
        int minorS = _player.getScore();
        if(minorS>0 && minorS!=majorS)
        {   // Two pairs
            fillHand(_player,_river);
            int finalScore = (((majorS-2)*(majorS-1))/2)+ (minorS) + 26;
            _player.setScore(finalScore);
        }
        else
        {   // Only one pair
            _player.setScore(13+majorS);
            fillHand(_player,_river);
        }
    }
}

//--------------------------------------------------------------------------------------
void hands::three(player &_player, const cardStack &_river)
{
    bool threeFound = false;
    unsigned int origHandSize = _player.getHand().size();
    cardStack spareCards;
    spareCards = findSpareCards(_player,_river);
    spareCards.sort();


    for(unsigned int i=0; !threeFound && i<spareCards.size()-2;i++)
    {
        for(unsigned int j=i+1; !threeFound && j<spareCards.size()-1;j++)
        {
            if(spareCards[i].getRank()==spareCards[j].getRank())
            {
                for(unsigned int k=j+1; !threeFound && k<spareCards.size();k++)
                {
                    if(spareCards[i].getRank()==spareCards[k].getRank())
                    {
                        _player.setHandCard(spareCards[i]);
                        _player.setHandCard(spareCards[j]);
                        _player.setHandCard(spareCards[k]);

                        int finalScore = 104+_player.getHandCard(origHandSize).getRank();
                        _player.setScore(finalScore);

                        fillHand(_player,_river);
                        threeFound = true;
                    }
                }
            }

        }
    }
}

//--------------------------------------------------------------------------------------
void hands::straight(player &_player, const cardStack &_river)
{
    cardStack spareCards;
    spareCards = findSpareCards(_player,_river);
    spareCards.sort();
    if(spareCards[3].getRank() < Rank::TEN)
    {
        spareCards.sortAceLow();
    }

    bool straightFound = false;
    for(unsigned int i=0; !straightFound && i<spareCards.size()-4;i++)
    {
        for(unsigned int j=i+1; !straightFound && j<spareCards.size()-3;j++)
        {
            // Check if First and Second are consecuative
            if(spareCards[i].getRank()==spareCards[j].getRank()+1)
            {
                for(unsigned int k=j+1; !straightFound && k<spareCards.size()-2;k++)
                {
                    // Check if Second and Third are consecuative
                    if(spareCards[j].getRank()==spareCards[k].getRank()+1)
                    {
                        for(unsigned int l=j+1; !straightFound && l<spareCards.size()-1;l++)
                        {
                            // Check if Third and Fourth are consecuative
                            if(spareCards[k].getRank()==spareCards[l].getRank()+1)
                            {
                                for(unsigned int m=l+1; !straightFound && m<spareCards.size();m++)
                                {
                                    // Check if Fourth and Fifth are consecuative
                                    if( ( spareCards[l].getRank() == spareCards[m].getRank()+1 ) ||
                                      ( ( spareCards[l].getRank() == Rank::TWO )                 &&
                                        ( spareCards[m].getRank() == Rank::ACE ) ) )
                                    {   // Player has a straight
                                        _player.setHandCard(spareCards[i]);
                                        _player.setHandCard(spareCards[j]);
                                        _player.setHandCard(spareCards[k]);
                                        _player.setHandCard(spareCards[l]);
                                        _player.setHandCard(spareCards[m]);

                                        int finalScore = 117;
                                        finalScore += _player.getHandCard(3).getRank();
                                        _player.setScore(finalScore);

                                        straightFound = true;
                                        fillHand(_player,_river);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

//--------------------------------------------------------------------------------------
void hands::flush(player &_player, const cardStack &_river)
{
  cardStack spareCards;
  spareCards = findSpareCards(_player,_river);
  spareCards.sort();

  bool flushFound = false;

  for(unsigned int i=0; !flushFound && i<spareCards.size()-4;i++)
  {
      for(unsigned int j=i+1; !flushFound && j<spareCards.size()-3;j++)
      {
          if(spareCards[i].getSuit()==spareCards[j].getSuit())
          {
              for(unsigned int k=j+1; !flushFound && k<spareCards.size()-2;k++)
              {
                  if(spareCards[j].getSuit()==spareCards[k].getSuit())
                  {
                      for(unsigned int l=k+1; !flushFound && l<spareCards.size()-1;l++)
                      {
                          if(spareCards[k].getSuit()==spareCards[l].getSuit())
                          {
                              for(unsigned int m=l+1; !flushFound && m<spareCards.size();m++)
                              {
                                  if(spareCards[l].getSuit()==spareCards[m].getSuit())
                                  {   // Player has a flush

                                      _player.setHandCard(spareCards[i]);
                                      _player.setHandCard(spareCards[j]);
                                      _player.setHandCard(spareCards[k]);
                                      _player.setHandCard(spareCards[l]);
                                      _player.setHandCard(spareCards[m]);
                                      // set score
                                      int finalScore = 127 -2;
                                      finalScore += _player.getHandCard(i).getRank();

                                      _player.setScore(finalScore);
                                      flushFound=true;
                                  }// end if
                              }// end for
                          }//end if
                      }//end for
                  }//end if
              }//end for
          }//end if
      }//end for
  }//end for
}

//--------------------------------------------------------------------------------------
void hands::fullHouse(player &_player, const cardStack &_river)
{
    three(_player,_river);
    if(_player.getScore() > 0)
    {
        int majorS = _player.getScore()-104;
        _player.setScore(0);
        _player.removeLastHandCard();
        _player.removeLastHandCard();
        pairs(_player,_river);
        if(_player.getScore() != majorS && _player.getScore() > 0)
        {
            // Player has full house
            int minorS = _player.getScore()-13;
            int finalScore = 140 + (12*(majorS - 1)) + minorS;
            _player.setScore(finalScore);
            _player.setKicker(0);
        }
        else
        {
            //empty hand and set score to 0
            _player.setScore(0);
            _player.setKicker(0);
            for (unsigned int i=0;i<_player.getHand().size();i++)
            {
                _player.removeLastHandCard();
            }
        }

    }
}

//--------------------------------------------------------------------------------------
void hands::four(player &_player, const cardStack &_river)
{
  cardStack tmpR1,tmpR2,tmpR3;
  tmpR1 = tmpR2 = tmpR3 = _river;
  player tmpP1,tmpP2,tmpP3;
  tmpP1 = tmpP2 = tmpP3 = _player;

  findPair(tmpP1,tmpR1);
  if (tmpP1.getScore() > 0)
  {
    tmpP2.removeHoleCard(tmpP1.getHandCard(0));
    tmpP2.removeHoleCard(tmpP1.getHandCard(1));
    tmpR2.removeCard(tmpP1.getHandCard(0));
    tmpR2.removeCard(tmpP1.getHandCard(1));

    findPair(tmpP2,tmpR2);
    if(tmpP2.getScore() > 0)
    {
        if(tmpP1.getScore() == tmpP2.getScore())
        {
            _player.setHandCard(tmpP1.getHandCard(0));
            _player.setHandCard(tmpP1.getHandCard(1));
            _player.setHandCard(tmpP2.getHandCard(0));
            _player.setHandCard(tmpP2.getHandCard(1));

            int finalScore = 296 + _player.getHandCard(0).getRank();
            _player.setScore(finalScore);

            fillHand(_player,_river);
            return;
        }
        tmpP3=tmpP2;
        tmpR3=tmpR2;
        tmpP3.removeHoleCard(tmpP2.getHandCard(0));
        tmpP3.removeHoleCard(tmpP2.getHandCard(1));
        tmpR3.removeCard(tmpP2.getHandCard(0));
        tmpR3.removeCard(tmpP2.getHandCard(1));

        findPair(tmpP3,tmpR3);
        if(tmpP3.getScore()==tmpP2.getScore())
        {
            _player.setHandCard(tmpP2.getHandCard(0));
            _player.setHandCard(tmpP2.getHandCard(1));
            _player.setHandCard(tmpP3.getHandCard(0));
            _player.setHandCard(tmpP3.getHandCard(1));

            int finalScore = 296 + _player.getHandCard(0).getRank();
            _player.setScore(finalScore);

            fillHand(_player,_river);
            return;
        }
    }
  }
}

//--------------------------------------------------------------------------------------
bool hands::checkStraightHasFlush(player &_player,          const cardStack &_river,
                                  const Suit::Value _suit,  unsigned int    _numSuit)
{
  if(_numSuit ==5){return true;}
  else if(_numSuit < 3){return false;}

  bool _flushFound = false;
  cardStack spareCards;
  spareCards = findSpareCards(_player,_river);
  spareCards.sort();
  for(unsigned int i=0; !_flushFound && i<spareCards.size()+1;i++)
  {
      bool suitFound = (spareCards[i].getSuitValue() == _suit);

      if(suitFound)
      {
          // Card of same suit present, now check whether it can go in straight
          int rankID = _player.getHand().findRankInStack(spareCards[i].getRank());

          if(rankID != -1)
          {
              // Replacement card of correct suit found.
              _numSuit++;
              _player.getHand().replaceCard(rankID,spareCards[i]);
              if(_numSuit == _player.getHand().size())
              {
                  //player has straight flush.
                  _player.getHand().replaceCard(rankID,spareCards[i]);
                  _flushFound = true;
              }
          }
          //else if(_player.getHand().findRankInStack(spareCards[i].getRank()+1)!=-1)
          else if((_player.getHandCard(4).getRank() == spareCards[i].getRank()+1) ||
                  (_player.getHandCard(4).getRank() == Rank::TWO &&
                   spareCards[i].getRank() == Rank::ACE))
          {
                if(_player.getHandCard(0).getSuitValue() != _suit)
                {
                    _numSuit++;
                }

                _player.removeHandCard(0);
                _player.setHandCard(spareCards[i]);
                // Card of same suit but small straight found
                if(_numSuit == _player.getHand().size())
                {
                    //playe has straight flush

                    _flushFound = true;
                }
          }

      }
  spareCards.removeCard(i);
  }
  return _flushFound;
}

//--------------------------------------------------------------------------------------
void hands::straightFlush(player &_player, const cardStack &_river)
{
    bool flushFound = false;
    unsigned int numHearts = 0;
    unsigned int numDiamonds = 0;
    unsigned int numSpades = 0;
    unsigned int numClubs = 0;

    straight(_player,_river);
    if(_player.getHand().size() != 0)
    {
        // Straight found now need to check for flush
        for(unsigned int i=0; i<_player.getHand().size();i++)
        {
            if     (_player.getHandCard(i).getSuitValue() == Suit::SPADE)  {numSpades++;}
            else if(_player.getHandCard(i).getSuitValue() == Suit::CLUB)   {numClubs++;}
            else if(_player.getHandCard(i).getSuitValue() == Suit::HEART)  {numHearts++;}
            else if(_player.getHandCard(i).getSuitValue() == Suit::DIAMOND){numDiamonds++;}
        }

        flushFound = checkStraightHasFlush(_player,_river,Suit::SPADE,numSpades);
        if(flushFound)
        {
            int finalScore = 309 + _player.getHandCard(3).getRank();
            _player.setScore(finalScore);
            return;
        }

        flushFound = checkStraightHasFlush(_player,_river,Suit::CLUB,numClubs);
        if(flushFound)
        {
            int finalScore = 309 + _player.getHandCard(3).getRank();
            _player.setScore(finalScore);
            return;
        }

        flushFound = checkStraightHasFlush(_player,_river,Suit::HEART,numHearts);
        if(flushFound)
        {
            int finalScore = 309 + _player.getHandCard(3).getRank();
            _player.setScore(finalScore);
            return;
        }

        flushFound = checkStraightHasFlush(_player,_river,Suit::DIAMOND,numDiamonds);
        if(flushFound)
        {
            int finalScore = 309 + _player.getHandCard(3).getRank();
            _player.setScore(finalScore);
            return;
        }

        if(!flushFound)
        {
            // No straight flush under straight.
            flushFound = false;
            _player.setScore(0);
            _player.setKicker(0);
            _player.emptyHand();
            return;
        }
    }
}

//-----------------------------------------------------------------------------
void hands::bestHand(player &_player, const cardStack &_river)
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

//--------------------------------------------------------------------------------------
std::vector<player> hands::tieBreak(std::vector<player> &_livePlayers, const std::vector<int> _ID)
{
  int topKicker = -1;
  std::vector<int> tieWinnerID;
  std::vector<player> tieWinners;
  for (unsigned int i=0; i<_ID.size(); i++)
  {
      // Find highest kicker
      topKicker = (_livePlayers[_ID[i]].getKicker()>topKicker)?
                   _livePlayers[_ID[i]].getKicker():topKicker;
  }

  // Check players that have top kicker
  for (unsigned int i=0;i<_ID.size();i++)
  {
      if (_livePlayers[_ID[i]].getKicker() == topKicker)
      {   tieWinnerID.push_back(_ID[i]);  }
  }

  // Push players with top kicker
  for (unsigned int i=0;i<tieWinnerID.size();i++)
  {
      _livePlayers[tieWinnerID[i]].printInfo();
      tieWinners.push_back(_livePlayers[tieWinnerID[i]]);
  }
  return tieWinners;
}

//--------------------------------------------------------------------------------------
std::vector<player> hands::winner(std::vector<player> &_livePlayers, const cardStack &_river)
{
    unsigned int numPlayers = _livePlayers.size();

    int topScore = 0;
    std::vector<int> winnerID;
    std::vector<player> WINNERS;

    // Find the highest score out of the players
    for (unsigned int i=0;i<numPlayers;i++)
    {
        hands::bestHand(_livePlayers[i],_river);
        topScore = (_livePlayers[i].getScore()>topScore)?
                    _livePlayers[i].getScore():topScore;

        _livePlayers[i].printInfo();
    }

    // Record player ID's that have top score
    for (unsigned int i=0;i<numPlayers;i++)
    {
        if (_livePlayers[i].getScore()==topScore)
        {   winnerID.push_back(i);    }
    }

    std::cout<<"\n========================================================\n";
    std::cout<<"\tWinner Winner, Chicken Dinner!!!";
    std::cout<<"\n========================================================\n";

    //check if there are multiple players with top score
    if (winnerID.size()>1)
    {
        // More than one player has the high score,
        // Now need to check these players Kicker,
        WINNERS = tieBreak(_livePlayers,winnerID);
    }
    else
    {
        // Only one winner
        _livePlayers[winnerID[0]].printInfo();
        WINNERS.push_back(_livePlayers[winnerID[0]]);
    }

    return WINNERS;
}
