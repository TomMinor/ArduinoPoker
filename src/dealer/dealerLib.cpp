#include "dealer/dealerLib.h"
#include <sstream>

//constructor
dealerLib::dealerLib()
{
  //shuffles the deck
  m_deck.shuffle();

}

//destructor
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
//  firstPlayersBet = playerBets.begin(); //  otherPlayersBet = playerBets.begin();

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

//if player has folded, remove them from the vectors
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
//returns true if number of players = 0
  if(m_numPlayers == 0){return true;}

//for every element in the array...
  for(int i=0;i<m_numPlayers;i++)
  {

//if a single element is false return false
      if(!_array[i])
      {
          return false;
      }
  }

//otherwise all elements would be true and so return true
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
      std::cout<<currentBet<<" current bet, "<<oldBet<<" old bet\n";
      for(unsigned int i=0;i<m_livePlayers.size();i++)
      {
          // find max bet
         int maxBet = checkMaxBet() - m_livePlayers[i].getBet();
         if(maxBet==0){p[i]=true;}
         else
         {
             if(!(Comms::receiveBet(m_deviceMap.at(m_livePlayers[i].getID()),playerBet,currentBet,maxBet)))
             {
                 // error, try to receive again
             }

             std::cout<<"player bet received from comms: "<<playerBet<<"\n";

             playerRaise = playerBet;
             playerBet += m_livePlayers[i].getBet();
             m_livePlayers[i].setBet(playerBet);

             // check if player has fold
             if(m_livePlayers[i].isFold())
             {

                 //GUI Stuff
                 //create visual represetation of the cards that get burnt
                 GUI::Hand* burned = m_dealerGui.uniqueHand(m_livePlayers[i].getHole(),m_livePlayers[i].getID());
                 //set their position off-screen
                 burned->setPos(m_dealerGui.getOffScreenPos(m_livePlayers[i].getID()));
                 //flip the cards
                 burned->setFlipped(true,true);
                 //move cards to the centre
                 burned->moveTo(m_dealerGui.getCentre());
                 //burn the cards
                 burned->burn();
                 //add the folded players bet to the pot
                 addBetToPot(playerBet);
                 //transfer the players information to m_table
                 updatePlayer(i);
                 //remove the player from the vector
                 m_livePlayers.erase(m_livePlayers.begin()+i);
                 //set the player to true
                 p[i] = true;
             }
             else
             {
                 //get the current players bet
                 currentBet = m_livePlayers[i].getBet();
                 //GUI runs bet animation
                 m_dealerGui.receiveBetFrom(m_livePlayers[i].getID(),playerRaise);

                 //if the players bet is the same as the previous players bet set the player to true
                 if(currentBet == oldBet)
                 {
                     p[i] = true;
                 }


                 else
                 {
                     //otherwise loop they've raised so loop through the live players
                     for(unsigned int j=0;j<m_livePlayers.size();j++)
                     {
                         //unless they're folded set everyone back to false'
                         if(m_livePlayers[j].isFold()) {p[j] = true;}

                         //otherwise false
                         else                          {p[j] = false;}
                     }
                     //set the current player to true
                     p[i]=true;
                 }
             }
             oldBet = currentBet;
         }
      }
  }
  //loop through live players
  for(unsigned int i=0;i<m_livePlayers.size();i++)
  {
     //get their bet and add it to the pot
      playerBet = m_livePlayers[i].getBet();
      addBetToPot(playerBet);
      //remove bet from their money
      m_livePlayers[i].removeBet();
      //transfer bet from liveplayer to table player
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
  //pop off top card of deck and set it as card
  PlayingCard card = m_deck.deal();
  //add it to the vector of public cards
  m_communityCards.push_back(card);
  //call gui function
  m_dealerGui.addPublicCard(card);
}
//--------------------------------------------------------------

//deals 2 cards to the players
void dealerLib::dealHands()
{

  std::vector<player>::iterator playerIt;

  //deal 2 cards to each person in the table by looping through each player twice
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

      //add card to the players vector of hole cards
      playerIt->setHoleCard(tmpCard);
      //call gui function
      m_dealerGui.dealCardTo(playerIt->getID(), tmpCard);

    }
  }

}
//-----------------------------------------------------------------------------------------
//calls guis update and draw functions
void dealerLib::update()
{
  m_dealerGui.update();
  m_dealerGui.draw();
}
//-----------------------------------------------------------------------------------------
//gets rid of all the cards and refills them
void dealerLib::reset()
{

  //loop through the players
  for(unsigned int i = 0; i < m_table.size(); i++)
  {
    //create visual represetation of the cards that get burnt
    GUI::Hand* burned = m_dealerGui.uniqueHand(m_table[i].getHole(), m_table[i].getID());
    //flip cards
    burned->setFlipped(true, true);
    //star card off the screen
    burned->setPos(m_dealerGui.getOffScreenPos(i));
    //move card onto the screen
    burned->setPos(m_dealerGui.getOnScreenPos(i));
    //burn card
    burned->burn();

    //remove all cards from hand
    m_table[i].emptyHole();
    //reset the fold values of player to false
    m_table[i].setFold(false);

  }

  //gui burn public card
  m_dealerGui.m_publicCards->burn();
  //remove all card from community card vector
  m_communityCards.erase(m_communityCards.begin(), m_communityCards.end());

  //reset the deck
  m_deck.reset();

  //reset live player vector
  m_livePlayers = m_table;


}



//-----------------------------------------------------------------------------------------
//works out the maximum bet
int dealerLib::checkMaxBet()
{

  std::vector<player>::iterator playerIt;

  //set default max bet ridiculously high
  int maxBet = 8000;

  //loop through live players
  for(playerIt = m_livePlayers.begin(); playerIt != m_livePlayers.end(); playerIt++)

  {
    //get current players money and if its less than the current max bet, set it as max bet
    int playerMoney = playerIt->getMoney();
    if(playerMoney < maxBet) {maxBet = playerMoney;}
  }
  return maxBet;
}

//-----------------------------------------------------------------------------------------


//initialise gui and map serial ports to player Ids
void dealerLib::init()
{

  //create std::map
  m_deviceMap = Comms::SerialPort::DetectSerialDevices();
  //set number of players as number of ports in use
  m_numPlayers = m_deviceMap.size();
  //loop through the map and initialise the player
  for (unsigned int i=0;i<m_deviceMap.size();i++)
  {
      initPlayer(i);
  }
  //create vector of visible players for the gui
  std::vector<const player*> guiPlayers;

  //add players to vector
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

//initialises the player
void dealerLib::initPlayer(const int &_id)
{
  //add player to the vector of players
  m_table.push_back(player());
  //set players ID to his position in vector
  m_table[_id].setID(_id);

  //ask player for a name
  std::string playerName;// = "default";
  if(!(Comms::receiveName(m_deviceMap.at(m_table[_id].getID()),playerName)))
  {
      //error request name again
  }

  //playerName = static_cast<std::ostringstream*>( &(std::ostringstream() <<_id) )->str();

  //set players name as his input
  std::cout<<"we have a name: "<<playerName<<"\n";
  m_table[_id].setName(playerName);
}

//-----------------------------------------------------------------------------------------


//remove player from
void dealerLib::removePlayer(std::vector<player>::iterator it)
{
//  m_dealerGui.kickPlayer(it->getID());
  m_table.erase(it);
}

//-----------------------------------------------------------------------------------------
//returns true if the player has ran out of money
bool dealerLib::checkIfLost(player _player)
{
  if(_player.getMoney() <= 0){return true;}
  else {return false;}
}

//-----------------------------------------------------------------------------------------
//kick the player from the game if he's ran out of money
void dealerLib::kickBrokePlayer()
{
  std::vector<player>::iterator playerIt;

  //iterate through all players and check if they've lost then kick if true
  for(playerIt = m_table.begin();playerIt != m_table.end(); playerIt++)
  {
    if(checkIfLost(*playerIt)) {removePlayer(playerIt);}
  }
}
//-----------------------------------------------------------------------------------------


int dealerLib::getNumPlayers()const
{
  return m_numPlayers;
}

//----------------------------------------------------------------------------------------

std::vector<player> dealerLib::getLivePlayers()const
{
  return m_livePlayers;
}

//--------------------------------------------------------------------------------------

void dealerLib::decideWinners()
{
  //create a vector of winning players
  std::vector<player> winners;
  std::vector<player>::iterator playerIt;

  //add the winning players to the vector
  winners = hands::winner(m_livePlayers, m_communityCards);

  //work out remainder by modulusing the pot by the number of winners
  int remainder = m_pot % winners.size();
  //check if there is a remainder
  bool remainderExists = isRemainder(remainder);
  // calculate the winnings each player would recieve
  int winnings = (m_pot - remainder) / winners.size();
  //create a vector of player IDs of the winners
  const std::vector<unsigned int> winnerIDs = getWinnerIds(winners);

  //call the gui function to visually display winners
  m_dealerGui.showWinner(winnerIDs, remainderExists, winnings);

  //loop through winners and add the winning to their money stash
  for(playerIt = winners.begin(); playerIt != winners.end(); playerIt++)
  {
    playerIt->receivePot(winnings);
  }

  //leave the remainder in the pot to be won next round
  m_pot = remainder;

}

//----------------------------------------------------------------------------------
//returns a vector of IDs from a player vector
std::vector<unsigned int> dealerLib::getWinnerIds(std::vector<player> _winners)
{
  //create ID vector
  std::vector<unsigned int> winnerIds;

  std::vector<player>::iterator playerIt;

  //iterate through player vector and add the ids of each player to the ID vector
  for(playerIt = _winners.begin(); playerIt != _winners.end(); playerIt++)
  {
    winnerIds.push_back(playerIt->getID());
  }

  return winnerIds;


}

//-----------------------------------------------------------------------------------
//returns true if remainder is greater than 0
bool dealerLib::isRemainder(int _remainder)
{
  if(_remainder > 0) {return true;}

  else {return false;}
}

//----------------------------------------------------------------------------------
//updates the values of the player from the live player vector
void dealerLib::updatePlayer(int _element)
{
  m_table[m_livePlayers[_element].getID()] = m_livePlayers[_element];
}
