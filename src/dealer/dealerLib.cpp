#include "dealer/dealerLib.h"


dealerLib::dealerLib()
{
  deck pack;
}

dealerLib::~dealerLib()
{

}
//--------------------------------------------------------------------------------------------------
void dealerLib::Betting()
{
//make a cooms object
  comms thing;

  std::vector<int> playerBets;
  std::vector<int>::iterator firstPlayersBet;
  std::vector<int>::iterator otherPlayersBet;
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
  playerItr = m_livePlayers.begin();

//while size of vector doesn't equal count, get bet info from comms...
  while(std::distance(playerBets.begin(), playerBets.end()) != count)
  {
    int maxBet = checkMaxBet();
    thing.sendBetLimits(*playerItr, (*playerItr).getBet(), maxBet);
    thing.receiveBet(*playerItr);

//if player has folded, remove them from the vectors
    if((*playerItr).fold)
    {
      m_pot += playerBets.at(*otherPlayersBet);
      playerBets.erase(otherPlayersBet);
      m_livePlayers.erase(playerItr);
      m_numPlayers = m_numPlayers - 1;
      maxBet = checkMaxBet();

    }

//set the bet placed
    playerBets.at(*otherPlayersBet) = (*playerItr).getBet();

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
    if(playerItr == m_livePlayers.end() -1) {playerItr = m_livePlayers.begin();}

    else{playerItr++;}


  }
//add all bets to the pot
  std::vector<int>::iterator betIt;
  for(betIt = playerBets.begin(); betIt != playerBets.end(); betIt++ )
  {
    m_pot += (*betIt);
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
//-----------------------------------------------------------------------------------------
void dealerLib::update()
{
//do some gui shiz
}
//-----------------------------------------------------------------------------------------
void dealerLib::resetCards()
{
  std::vector<player>::iterator playerIt;
  cardStack::iterator cardIt;



  for(playerIt=m_table.begin(); playerIt!=m_table.end(); playerIt++)
  {
    (*playerIt).emptyHole();
  }


  for(int i=0; i<5; i++)
  {
    m_communityCards.pop_back();
  }
}

//-----------------------------------------------------------------------------------------

int dealerLib::checkMaxBet()
{
  std::vector<player>::iterator playerIt;
  int maxBet = 8000;

  for(playerIt = m_livePlayers.begin(); playerIt != m_livePlayers.end(); playerIt++)
  {
    int playerMoney = (*playerIt).getMoney();
    if(playerMoney < maxBet) {maxBet = playerMoney;}
  }
  return maxBet;
}

//-----------------------------------------------------------------------------------------

void dealerLib::initialisePlayers()
{
  comms com; 

  for(int i = 0; i < m_numPlayers; i++)
  {
    m_table.push_back(player());
    m_table[i].setName(std::string("blah"));



  }

  std::vector<player>::iterator playerIt;

  for(playerIt = m_table.begin();playerIt != m_table.end(); playerIt++)
  {
    //requestNameInput();
    com.receiveName(*playerIt);
  }

}

//-----------------------------------------------------------------------------------------

void dealerLib::clearTable()
{
  for(int i = 0; i < m_numPlayers; i++)
  {
    m_table.pop_back();
  }
}

//-----------------------------------------------------------------------------------------

void dealerLib::removePlayer(std::vector<player>::iterator it)
{
  m_table.erase(it);
}

//-----------------------------------------------------------------------------------------

bool dealerLib::checkIfLost(player _player)
{
  if(_player.getMoney() <= 0){return true;}
  else {return false;}
}

//-----------------------------------------------------------------------------------------

void dealerLib::removeTheNoobs()
{
  std::vector<player>::iterator playerIt;

  for(playerIt = m_table.begin();playerIt != m_table.end(); playerIt++)
  {
    if(checkIfLost(*playerIt)) {removePlayer(playerIt);}
  }
}
//-----------------------------------------------------------------------------------------



