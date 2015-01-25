#include "dealer/dealerLib.h"
#include <sstream>


dealerLib::dealerLib()
{
  m_deck.shuffle();

}

dealerLib::~dealerLib()
{

}
//--------------------------------------------------------------------------------------------------
//void dealerLib::Betting()
//{
////make a cooms object
//  std::vector<int> playerBets;
//  std::vector<int>::iterator firstPlayersBet;
//  std::vector<int>::iterator otherPlayersBet;
//  int count = 0;
//  unsigned int currentBet = 0;

//// initialise betting iterators
//  firstPlayersBet = playerBets.begin();
//  otherPlayersBet = playerBets.begin();

////initialise vector of bets
//  for(int i=0;i<m_numPlayers;i++)
//  {
//    playerBets.push_back(0);
//  }

////make iterator for m_table
//  std::vector<player>::iterator playerItr;
//  playerItr = m_livePlayers.begin();

////while size of vector doesn't equal count, get bet info from comms...

//  while(std::distance(playerBets.begin(), playerBets.end()) != count && m_numPlayers > 1)
//  {

//  //if current position is end of vector set it to beginning of vector
//    if(otherPlayersBet == playerBets.end()) {otherPlayersBet = playerBets.begin();}

//    int maxBet = checkMaxBet();


//    Comms::sendBetLimits(*playerItr, (*playerItr).getBet(), maxBet);
//    // sendBetLimits should send player and min and max bet limits
//    //thing.receiveBet(*playerItr);
//    currentBet = playerItr->getBet();

////if player has folded, remove them from the vectors
//    if((*playerItr).isFold())
//    {
//      m_pot += playerBets.at(*otherPlayersBet);
//      playerBets.erase(otherPlayersBet);
//      m_livePlayers.erase(playerItr);
//      m_numPlayers = m_numPlayers - 1;
//      maxBet = checkMaxBet();

//    }
//    else
//    {

//  //set the bet placed
//      playerBets.at(*otherPlayersBet) = (*playerItr).getBet();

//  //if bet matches previous persons bet increment count
//      if(*firstPlayersBet == *otherPlayersBet)
//      {
//        count++;
//      }

//  //otherwise reset count to 0 and firstplayersbet points to current position
//      else
//      {
//       count = 0;
//       firstPlayersBet = otherPlayersBet;
//      }


//  //otherwise move to next players bet


//  //move to next player in m_table
//      if(playerItr == m_livePlayers.end() -1) {playerItr = m_livePlayers.begin();}

//      else{playerItr++;}


//      {otherPlayersBet++;}


//    }



//  }
////add all bets to the pot
//  std::vector<int>::iterator betIt;
//  for(betIt = playerBets.begin(); betIt != playerBets.end(); betIt++ )
//  {
//    m_pot += (*betIt);
//  }

//}


bool dealerLib::checkBoolArray(bool _array[])const
{
  if(m_numPlayers == 0){return true;}
  for(int i=0;i<m_numPlayers;i++)
  {
      if(!_array[i])
      {
          return false;
      }
  }
  return true;
}

//---------------------------------------------------------

void dealerLib::bet()
{
  std::cout<<"enter bet method\n";
  Uint16 currentBet = 0;
  Uint16 oldBet = 0;
  Uint16 playerBet = 0;
  Uint16 playerRaise = 0;
  bool p[m_livePlayers.size()];

  //When all bets are matched the array will all be true
  //Thus breaking out of the while loop
  while(!(checkBoolArray(p)))
  {
      std::cout<<"enter bet WHILE LOOP\n";
      for(unsigned int i=0;i<m_livePlayers.size();i++)
      {
          std::cout<<"enter bet FOR LOOP\n";
          // find max bet
         int maxBet = checkMaxBet() - m_livePlayers[i].getBet();
         if(maxBet==0){p[i]=true;}
         else
         {
             std::cout<<"MAX BET greater than 0\n";
//             if(!(Comms::receiveBet(m_deviceMap.at(m_livePlayers[i].getID()),playerBet,currentBet,maxBet)))
//             {
//                 // error, try to receive again
//             }

             std::cout<<"player bet received from comms: "<<playerBet<<"\n";
             playerBet = 100;
             std::cout<<"player bet manually set: "<<playerBet<<"\n";

             playerRaise = playerBet;
             playerBet += m_livePlayers[i].getBet();
             m_livePlayers[i].setBet(playerBet);

             // check if player has fold
             if(m_livePlayers[i].isFold())
             {
                 std::cout<<"Player"<<m_livePlayers[i].getID()<<" folded\n";
                 // remove player from live players
                 //playerBet = m_livePlayers[i].getBet();
                 GUI::Hand* burned = m_dealerGui.uniqueHand(m_livePlayers[i].getHole(),m_livePlayers[i].getID());
                 burned->setPos(m_dealerGui.getOffScreenPos(m_livePlayers[i].getID()));
                 burned->setFlipped(true,true);
                 burned->moveTo(m_dealerGui.getCentre());
                 burned->burn();
                 addBetToPot(playerBet);
                 updatePlayer(i);
                 m_livePlayers.erase(m_livePlayers.begin()+i);
                 p[i] = true;
             }
             else
             {
                 std::cout<<"player made bet\n";
                 currentBet = m_livePlayers[i].getBet();
                 m_dealerGui.receiveBetFrom(m_livePlayers[i].getID(),playerRaise);
                 std::cout<<"past gui method receiveBetFrom\n";
                 if(currentBet == oldBet)
                 {
                     p[i] = true;
                     std::cout<<"Player MATCHED BET\n";
                 }
                 else
                 {
                     std::cout<<"Player RAISED\n";
                     for(unsigned int j=0;j<m_livePlayers.size();j++)
                     {
                         if(j==i)                           {p[j]=true;}
                         else if(m_livePlayers[j].isFold()) {p[j] = true;}
                         else                               {p[j] = false;}
                     }
                 }
             }
             oldBet = currentBet;
         }
      }
  }
  for(unsigned int i=0;i<m_livePlayers.size();i++)
  {
      playerBet = m_livePlayers[i].getBet();
      addBetToPot(playerBet);
      m_livePlayers[i].removeBet();
      updatePlayer(i);
  }

}

void dealerLib::addBetToPot(const int &_bet)
{
  m_pot += _bet;
}

//--------------------------------------------------------------
//deals out the first three community cards
void dealerLib::dealFlop()
{
  for(int i=0; i<3; i++)

  {
    PlayingCard card = m_deck.deal();
    m_communityCards.push_back(card);
    m_dealerGui.addPublicCard(card);
  }
}
//--------------------------------------------------------------

//deals adds an extra card to the community cards. Used for the river and the turn
void dealerLib::dealRiverTurn()
{
  PlayingCard card = m_deck.deal();
  m_communityCards.push_back(card);
  m_dealerGui.addPublicCard(card);
}
//--------------------------------------------------------------

//deals 2 cards to the players
void dealerLib::dealHands()
{
  std::vector<player>::iterator playerIt;
  for(int i=0; i<2; i++)
  {
    for(playerIt = m_table.begin(); playerIt != m_table.end(); playerIt++)
    {
      PlayingCard tmpCard = m_deck.deal();
      //if(!(Comms::sendCard(*playerIt, tmpCard)))
      if(!(Comms::sendCard(m_deviceMap.at(playerIt->getID()),tmpCard)))
      {
          //error re-send card
      }

      playerIt->setHoleCard(tmpCard);
      m_dealerGui.dealCardTo(playerIt->getID(), tmpCard);

    }
  }

}
//-----------------------------------------------------------------------------------------
void dealerLib::update()
{
  m_dealerGui.update();
  m_dealerGui.draw();
}
//-----------------------------------------------------------------------------------------
void dealerLib::reset()
{


  for(unsigned int i = 0; i < m_table.size(); i++)
  {

    GUI::Hand* burned = m_dealerGui.uniqueHand(m_table[i].getHole(), m_table[i].getID());
//    burned->setFlipped(true, true);
    burned->setPos(m_dealerGui.getOffScreenPos(i));
    burned->setPos(m_dealerGui.getOnScreenPos(i));
    burned->burn();

    m_table[i].emptyHole();
    m_table[i].setFold(false);

  }
  m_dealerGui.m_publicCards->burn();
  m_communityCards.erase(m_communityCards.begin(), m_communityCards.end());

  m_deck.reset();


  m_livePlayers = m_table;





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

void dealerLib::init()
{

  m_deviceMap = Comms::SerialPort::DetectSerialDevices();

  m_numPlayers = m_deviceMap.size();
  for (unsigned int i=0;i<m_deviceMap.size();i++)
  {
      initPlayer(i);
  }
  std::vector<const player*> guiPlayers;
  for(unsigned int i=0;i<m_numPlayers;i++)
  {
      guiPlayers.push_back(&m_table[i]);
  }
  cardStack flop;
  m_dealerGui.initialise(guiPlayers,flop);
  //m_dealerGui.m_publicCards->killNow();

  m_livePlayers = m_table;
}

//-----------------------------------------------------------------------------------------

void dealerLib::initPlayer(const int &_id)
{
  m_table.push_back(player());
  m_table[_id].setID(_id);
  std::string playerName = "default";
  //if(!(Comms::receiveName(m_deviceMap.at(m_table[_id].getID()),playerName)))
  {
      //error request name again
  }

  playerName = static_cast<std::ostringstream*>( &(std::ostringstream() <<_id) )->str();

  std::cout<<"we have a name: "<<playerName<<"\n";
  m_table[_id].setName(playerName);
}

//-----------------------------------------------------------------------------------------

void dealerLib::clearTable()
{
  m_table.erase(m_table.begin(), m_table.end());
}

//-----------------------------------------------------------------------------------------

void dealerLib::removePlayer(std::vector<player>::iterator it)
{
//  m_dealerGui.kickPlayer(it->getID());
  m_table.erase(it);
}

//-----------------------------------------------------------------------------------------

bool dealerLib::checkIfLost(player _player)
{
  if(_player.getMoney() <= 0){return true;}
  else {return false;}
}

//-----------------------------------------------------------------------------------------

void dealerLib::kickBrokePlayer()
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


int dealerLib::getNumPlayers()const
{
  return m_numPlayers;
}

std::vector<player> dealerLib::getLivePlayers()const
{
  return m_livePlayers;
}

void dealerLib::decideWinners()
{
  std::vector<player> winners;
  std::vector<player>::iterator playerIt;
  winners = hands::winner(m_livePlayers, m_communityCards);
  int remainder = m_pot % winners.size();
  bool remainderExists = isRemainder(remainder);

  int winnings = (m_pot - remainder) / winners.size();

  getWinnerIds(winners);

  for(playerIt = winners.begin(); playerIt != winners.end(); playerIt++)
  {
    playerIt->receivePot(winnings);
  }

  m_pot = remainder;




}

std::vector<int> dealerLib::getWinnerIds(std::vector<player> _winners)
{
  std::vector<int> winnerIds;

  std::vector<player>::iterator playerIt;

  for(playerIt = _winners.begin(); playerIt != _winners.end(); playerIt++)
  {
    winnerIds.push_back(playerIt->getID());
  }

  return winnerIds;


}

bool dealerLib::isRemainder(int _remainder)
{
  if(_remainder > 0) {return true;}

  else {return false;}
}

void dealerLib::updatePlayer(int _element)
{
  m_table[m_livePlayers[_element].getID()] = m_livePlayers[_element];
}
