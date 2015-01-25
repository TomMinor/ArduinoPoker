#include <iostream>
#include "dealer/dealerLib.h"
#include <ctime>
#include <cstdlib>
#include <math.h>
#include "dealer/pokerHands.h"
#include <SDL/SDL.h>
#include <SDL2/SDL.h>



//std::vector<PlayingCard>::iterator it;

//int myRandom(int i)
//{
//    return(std)
//}



//int main()
//{
//  std::srand( unsigned ( std::time(0) ) );

//  deck Deck;
//  Deck.shuffle();
//  Deck.printDeck();


//  return EXIT_SUCCESS;

//  dealerLib table;

//  /*
//  table.initialiseDeck();
//  table.dealHands();
//  table.Betting();
//  table.dealFlop();
//  table.Betting();
//  table.dealRiverTurn();
//  table.Betting();
//  table.dealRiverTurn();
//  table.betting();
//  check whose won and stuff
//  table.removeTheNoobs();
//  table.burndeck();

//  */



//}


int main()
{
    //GUI::DealerGUI gui;

    std::vector<player> players;

    std::cout<<"Initialising players\n";

    player p1;
    p1.setName(std::string("dick"));
    players.push_back(p1);
    player p2;
    p2.setName(std::string("butt"));
    players.push_back(p2);
    player p3;
    p3.setName(std::string("buck"));
    players.push_back(p3);
    player p4;
    p4.setName(std::string("ditt"));
    players.push_back(p4);

    std::cout<<"Initialised all players\n";

    PlayingCard aceOfSpades = PlayingCard(Rank::ACE,Suit::SPADE);
    std::vector<PlayingCard> cardList;
    cardList.push_back(aceOfSpades);
    p1.setHandCard(aceOfSpades);
    p2.setHandCard(aceOfSpades);
    p3.setHandCard(aceOfSpades);
    p4.setHandCard(aceOfSpades);
    std::vector<player*> winningPlayers;
    winningPlayers.push_back(&p3);
    winningPlayers.push_back(&p4);
    //Uint16 amount = 100;

    //gui.initialise(players, cardList);

    SDL_Event event;
    bool quit=false;

    dealerLib table;
    table.init();

    deck pack;
    pack.init();


//    while (!quit)
//    {
        if(table.getNumPlayers() == 1)
          {
            quit =true;
            std::cout<<"only one player at the moment \n";
          }
        table.dealHands(pack);//call gui.dealCardTo(playerID,PlayingCard)


        table.bet();//internally call gui.receiveBetFrom(playerID,amount)


        //Burning deck card method:
//        GUI::Card* burned = gui.uniqueCard(PlayingCard(Rank::ACE,Suit::SPADE),GUI::LEFT);
//        burned->setFlipped(true,true);
//        burned->setPos(gui.getDeckPos());
//        burned->updateRect();
//        burned->burn();
        //table.dealFlop();//internally call addPublicCard(PlayingCard) x3

        //table.bet();//internally call gui.receiveBetFrom(playerID,amount)
                        //call gui.receiveBetFrom(playerID,Unit16 amount,bool isFirstBet)

        //table.dealRiverTurn();//internally calladdPublicCard(PlayingCard)

        //table.bet();//internally call gui.receiveBetFrom(playerID,amount)
                        //call gui.receiveBetFrom(playerID,Unit16 amount,bool isFirstBet)

        //table.dealRiverTurn();//internally calladdPublicCard(PlayingCard)

        //table.bet();//internally call gui.receiveBetFrom(playerID,amount)
        //call gui.receiveBetFrom(playerID,Unit16 amount,bool isFirstBet)

        //std::vector<player> winners;
        //winners = hands::winner(table.getLivePlayers(),table.m_communityCards);
        //gui.showWinner(&winners);
        //unsigned int winnings = table.getPot() / winners.size();

//        for(unsigned int i=0; i<winners.size();i++)
//        {
//            winners[i].receivePot(winnings);
//        }


//        while ( SDL_PollEvent(&event) )
//        {
//            switch (event.type)
//            {
//                // this is the window x being clicked.
//                case SDL_QUIT : quit = true; break;

//                // now we look for a keydown event
//                case SDL_KEYDOWN:
//                {
//                    switch( event.key.keysym.sym )
//                    {
//                        // if it's the escape key quit
//                        case SDLK_ESCAPE :  quit = true; break;
//                    }
//                }

//                default : break;
//            }
//        }// end of event while loop

        //SDL_Delay(32);
    //}
    return EXIT_SUCCESS;
}

