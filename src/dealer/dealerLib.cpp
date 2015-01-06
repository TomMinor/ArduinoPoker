#include "dealer/dealerLib.h"

dealerLib::dealerLib()
{

}

dealerLib::~dealerLib()
{

}

void dealerLib::Betting()
{

}

void dealerLib::dealFlop(deck _pack)
{
  for(int i=0; i<3; i++)
    m_communityCards.push_back(_pack.deal());
}

void dealerLib::dealRiverTurn(deck _pack)
{
  m_communityCards.push_back(_pack.deal());
}

void dealerLib::dealHands(deck _pack)
{
  std::vector<player>::iterator playerIt;
  for(int i=0; i<2; i++)
  {
    for(playerIt = m_table.begin(); playerIt != m_table.end(); playerIt++)
    {
      playerIt->setHoleCard(_pack.deal());
    }
  }

}
