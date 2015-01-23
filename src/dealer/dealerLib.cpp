#include "dealer/dealerLib.h"


dealerLib::dealerLib()
{

}

dealerLib::~dealerLib()
{

}

void dealerLib::Betting()
{
//make a cooms object
  comms thing;

  std::vector<int> playerBets;
  std::vector<int>::iterator firstPlayersBet;
  std::vector<int>::iterator otherPlayersBet;
//  std::vector<int>::iterator betItr;
  int count = 0;

// initialise betting iterators
  firstPlayersBet = playerBets.begin();
  otherPlayersBet = playerBets.begin();

//initialise vector of bets
  for(int i=0;i<m_numPlayers;i++)
  {
    playerBets.push_back(0);
  }

//make iterator for m_table
  std::vector<player>::iterator playerItr;

//while size of vector doesn't equal count, get bet info from comms...
  while(std::distance(playerBets.begin(), playerBets.end()) != count)
  {
    thing.sendBetLimits(*playerItr, (*playerItr).m_bet, (*playerItr).getMoney());
    thing.receiveBet(*playerItr);

//if player has folded, remove them from the vectors
    if(fold)
    {
      playerBets.erase(otherPlayersBet);
      m_table.erase(playerItr);
      m_numPlayers = m_numPlayers - 1;

    }

//set the bet placed
    playerBets.at(*otherPlayersBet) = (*playerItr).m_bet;
//if bet matches previous persons bet increment count
    if(*firstPlayersBet == *otherPlayersBet)
    {
      count++;
    }

//otherwise reset count to 0 and firstplayersbet points to current position
    else
    {
     count = 0;
     firstPlayersBet = otherPlayersBet;
    }

//if current position is end of vector set it to beginning of vector
    if(otherPlayersBet == playerBets.end() - 1) {otherPlayersBet = playerBets.begin();}
//otherwise move to next players bet
    else {otherPlayersBet++;}

//move to next player in m_table
    playerItr++;


  }


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
  comms thing;

  std::vector<player>::iterator playerIt;
  for(int i=0; i<2; i++)
  {
    for(playerIt = m_table.begin(); playerIt != m_table.end(); playerIt++)
    {
      PlayingCard tmpCard = _pack.deal();
      playerIt->setHoleCard(tmpCard);
      thing.sendCard(*playerIt, tmpCard);
    }
  }

}

void dealerLib::update()
{
//do some gui shiz
}


