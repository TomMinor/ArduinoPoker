#include <iostream>
#include "dealer/dealerLib.h"
#include <ctime>
#include <cstdlib>

//std::vector<PlayingCard>::iterator it;

//int myRandom(int i)
//{
//    return(std)
//}



int main()
{
  std::srand( unsigned ( std::time(0) ) );

  deck Deck;
  Deck.shuffle();
  Deck.printDeck();


  return EXIT_SUCCESS;

  dealerLib table;

  /*
   * table.dealHands();
     table.Betting();
    table.dealFlop();
    table.Betting();
    table.dealRiverTurn();
    table.Betting();
    table.dealRiverTurn();
    table.betting();
  check whose won and stuff
  table.checkLosersandkick();

  */



}


