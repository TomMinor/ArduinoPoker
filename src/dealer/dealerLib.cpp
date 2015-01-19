#include "dealer/dealerLib.h"

dealerLib::dealerLib()
{

}

dealerLib::~dealerLib()
{

}

void dealerLib::Betting()
{
//  std::vector<int> playerBets;
//  std::vector<int>::iterator firstPlayersBet;
//  std::vector<int>::iterator otherPlayersBet;
//  std::vector<int>::iterator betItr;
//  int count = 0;

//  firstPlayersBet = playerBets.begin();
//  otherPlayersBet = playerBets.begin();

//  std::vector<player>::iterator playerItr;

//  while(std::distance(playerBets.begin(), playerBets.end()) != count)
//  {

//    playerBets.push_back(m_bet); //playerItr->m_table.getBet() need to implement a getBet function
//    if(*firstPlayersBet == *otherPlayersBet)
//    {
//      count++;
//    }
//    else
//    {count = 0;
//     firstPlayersBet = otherPlayersBet;
//    }
//    if(otherPlayersBet == playerBets.end()) {otherPlayersBet = playerBets.begin();}

//    else {otherPlayersBet++;}


//  }


}
//--------------------------------------------------------------
//deals out the first three community cards
void dealerLib::dealFlop(deck _pack)
{
  for(int i=0; i<3; i++)
    m_communityCards.push_back(_pack.deal());
}
//--------------------------------------------------------------

//deals adds an extra card to the community cards. Used for the river and the turn
void dealerLib::dealRiverTurn(deck _pack)
{
  m_communityCards.push_back(_pack.deal());
}
//--------------------------------------------------------------

//deals 2 cards to the players
void dealerLib::dealHands(deck _pack)
{
  std::vector<player>::iterator playerIt;
  for(int i=0; i<2; i++)
  {
    for(playerIt = m_table.begin(); playerIt != m_table.end(); playerIt++)
    {

      playerIt->setHoleCard(_pack.deal());
      //sendHand(playerIt, m_hand);
    }
  }

}

void dealerLib::update()
{
//do some gui shiz
}

bool dealerLib::sendBetLimits(player _player, unsigned int _min, unsigned int _max)
{

}

bool dealerLib::sendCard(player _player, PlayingCard _card)
{

}

bool dealerLib::sendHand(player _player, cardStack _cards)
{

}

bool dealerLib::recieveBet(player _player, unsigned int &_bet, unsigned int _timeout)
{

}

bool dealerLib::recieveName(player _player, std::string &_name, unsigned int _timeout)
{

}
