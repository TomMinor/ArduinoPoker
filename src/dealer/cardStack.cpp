#include "dealer/cardStack.h"
#include <algorithm>
#include <iostream>


cardStack::cardStack()
{

}

cardStack::~cardStack()
{

}

bool cardStack::lowToHigh(const PlayingCard &_a,const PlayingCard &_b)
{
    return (_a.getRank()<_b.getRank());
}
//----------------------------------------------------------------------
bool cardStack::highToLow(const PlayingCard &_a, const PlayingCard &_b)
{
    return (_a.getRank()>_b.getRank());
}
//----------------------------------------------------------------------
//----------------------------------------------------------------------
void cardStack::addCard(const PlayingCard &_card)
{
  push_back(_card);
}
//----------------------------------------------------------------------
//----------------------------------------------------------------------
PlayingCard cardStack::getCard(const int _i)
{
  return ((std::vector<PlayingCard>)*this)[_i];
}
//----------------------------------------------------------------------
PlayingCard cardStack::getHighestCard()
{
  if(size()<2 && size()!=0)
  {
      return getCard(0);
  }
  PlayingCard highCard = getCard(0);
  for(unsigned int i=1; i<size();i++)
  {
      if(getCard(i).getRank()>highCard.getRank())
      {
          highCard = getCard(i);
      }
  }
  return highCard;
}
//----------------------------------------------------------------------
bool cardStack::findCard(const PlayingCard &_card)
{
//  for(unsigned int i=0; i<size();i++)
//  {

//  }

}
int cardStack::findRankInStack(const int _rank)
{
  bool rankFound = false;

  for(unsigned int i=0; i<size();i++)
  {
    if(_rank == getCard(i).getRank())
    {
        rankFound = true;
        return i;
    }
  }
  return -1;

}

int cardStack::findSuitInStack(const int _suit)
{
  bool suitFound = false;

  for(unsigned int i=0; i<size();i++)
  {
    if(_suit == getCard(i).getSuit())
    {
        suitFound = true;
        return i;
    }
  }
  return -1;

}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
void cardStack::removeCard(const PlayingCard &_card)
{
  //bool cardFound;

  // Find card in player Hole cards
  for (unsigned int i=0;i<size();i++)
  {
    //cardFound= false;
    if(getCard(i)==_card)
    {
        erase(begin()+i,begin()+i+1);
        //cardFound = true;
        return;
    }
  }
}
//----------------------------------------------------------------------
void cardStack::removeCard(const int _i)
{
  erase(begin()+_i,begin()+_i+1);
}
//----------------------------------------------------------------------
void cardStack::emptyStack()
{
  erase(begin(),end());
}
//----------------------------------------------------------------------
void cardStack::replaceCard(const int _i, const PlayingCard &_card)
{
  ((std::vector<PlayingCard>)*this)[_i] = _card;
}


//----------------------------------------------------------------------
//----------------------------------------------------------------------
void cardStack::sort()
{
  std::sort(begin(),end(),highToLow);
}
//----------------------------------------------------------------------
void cardStack::reverseSort()
{
  std::sort(begin(),end(),lowToHigh);
}
//----------------------------------------------------------------------

