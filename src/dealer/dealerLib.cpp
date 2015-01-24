#include "dealer/dealerLib.h"


dealerLib::dealerLib()
{
  m_deck.shuffle();
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
  unsigned int currentBet = 0;

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

  while(std::distance(playerBets.begin(), playerBets.end()) != count && m_numPlayers > 1)
  {

  //if current position is end of vector set it to beginning of vector
    if(otherPlayersBet == playerBets.end()) {otherPlayersBet = playerBets.begin();}

    int maxBet = checkMaxBet();

    thing.sendBetLimits(*playerItr, (*playerItr).getBet(), maxBet);
    // sendBetLimits should send player and min and max bet limits
    thing.receiveBet(*playerItr);
    currentBet = playerItr->getBet();

//if player has folded, remove them from the vectors
    if((*playerItr).fold)
    {
      m_pot += playerBets.at(*otherPlayersBet);
      playerBets.erase(otherPlayersBet);
      m_livePlayers.erase(playerItr);
      m_numPlayers = m_numPlayers - 1;
      maxBet = checkMaxBet();

    }
    else
    {

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


  //otherwise move to next players bet


  //move to next player in m_table
      if(playerItr == m_livePlayers.end() -1) {playerItr = m_livePlayers.begin();}

      else{playerItr++;}


      {otherPlayersBet++;}


    }



  }
//add all bets to the pot
  std::vector<int>::iterator betIt;
  for(betIt = playerBets.begin(); betIt != playerBets.end(); betIt++ )
  {
    m_pot += (*betIt);
  }


}



void dealerLib::bet()
{
  comms tom;
  int currentBet = 0;
  int oldBet = 0;
  int playerBet = 0;
  bool p[4];
  p[0] = p[1] = p[2] = p[3] = false;

  while(!(p[0] && p[1] && p[2] && p[3]))
  {
      for(unsigned int i=0;i<m_livePlayers.size();i++)
      {
          // find max bet
         int maxBet = checkMaxBet() - m_livePlayers[i].getBet();
         tom.sendBetLimits(m_livePlayers[i],currentBet,maxBet);
         tom.receiveBet(m_livePlayers[i]);

         // check if player has fold
         if(m_livePlayers[i].fold)
         {
             // remove player from live players
             playerBet = m_livePlayers[i].getBet();
             addBetToPot(playerBet);
             m_livePlayers.erase(m_livePlayers.begin()+i);
             p[i] = true;
         }
         else
         {
             currentBet = m_livePlayers[i].getBet();
             if(currentBet == oldBet)
             {
                 p[i] = true;
             }
             else
             {
                 for(unsigned int j=0;j<m_livePlayers.size();j++)
                 {
                     if(j==i){p[j]=true;}
                     else if(m_livePlayers[j].fold)
                     {
                         p[j] = true;
                     }
                     else{p[j] = false;}
                 }
             }
         }
         oldBet = currentBet;
      }
  }
  for(unsigned int i=0;i<m_livePlayers.size();i++)
  {
      playerBet = m_livePlayers[i].getBet();
      addBetToPot(playerBet);
      m_livePlayers[i].removeBet();
  }
}

void dealerLib::addBetToPot(const int &_bet)
{
  m_pot += _bet;
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
      //Could do it like this? playerIt->setHoleCard(_pack.deal());
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

  for(playerIt=m_table.begin(); playerIt!=m_table.end(); playerIt++)
  {
    playerIt->emptyHole();
  }

  m_communityCards.erase(m_communityCards.begin(), m_communityCards.end());

  m_deck.reset();



}



//-----------------------------------------------------------------------------------------

int dealerLib::checkMaxBet()
{
  std::vector<player>::iterator playerIt;
  int maxBet = 8000;

  for(playerIt = m_livePlayers.begin(); playerIt != m_livePlayers.end(); playerIt++)

  {
    int playerMoney = playerIt->getMoney();
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


//void dealerLib::addBetsToPot()
//{

//}


bool dealerLib::callComms(commsRequest request)
{
  switch (request){
    case sendBetLimits:

      break;

    case sendMoney:
      break;

    case sendCard:
      break;

    case getName:
      break;

    case getBet:
      break;

    case wait:
      break;

    default:
      break;
    }
}


int dealerLib::getNumPlayers()const
{
  return m_numPlayers;
}

std::vector<player> dealerLib::getLivePlayers()const
{
  return m_livePlayers;
}
