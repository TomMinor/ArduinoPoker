#include <iostream>
#include "dealer/dealerLib.h"
#include <ctime>
#include <cstdlib>
#include <math.h>
#include "dealer/pokerHands.h"
#include <SDL/SDL.h>
#include <SDL2/SDL.h>
#include <QTimer>

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

Uint32 updateComms(Uint32 interval, void *parm)
{
  static bool lock = false;

  if(!lock)
  {
      lock = true;

      dealerLib* myTable = reinterpret_cast<dealerLib*>(parm);
//      myTable->dealHands();
//      myTable->bet();
//      myTable->dealFlop();
//      myTable->bet();
//      myTable->dealRiverTurn();
//      myTable->bet();
//      myTable->dealRiverTurn();
//      myTable->bet();


      printf("HNNGGH!");
      SDL_Delay(1000);
      lock= false;
  }

  return interval;
}

int main()
{
    //GUI::DealerGUI gui;
//    std::vector<player> players;

//    player p1;
//    p1.setName(std::string("dick"));
//    players.push_back(p1);
//    player p2;
//    p2.setName(std::string("butt"));
//    players.push_back(p2);
//    player p3;
//    p3.setName(std::string("buck"));
//    players.push_back(p3);
//    player p4;
//    p4.setName(std::string("ditt"));
//    players.push_back(p4);


//    PlayingCard aceOfSpades = PlayingCard(Rank::ACE,Suit::SPADE);
//    std::vector<PlayingCard> cardList;
//    cardList.push_back(aceOfSpades);
//    p1.setHandCard(aceOfSpades);
//    p2.setHandCard(aceOfSpades);
//    p3.setHandCard(aceOfSpades);
//    p4.setHandCard(aceOfSpades);
//    std::vector<player*> winningPlayers;
//    winningPlayers.push_back(&p3);
//    winningPlayers.push_back(&p4);

    SDL_Event event;
    bool quit=false;

    dealerLib table;
    table.init();

    deck pack;
    pack.initDeck();


    int running = 1;
    int last_time = 0;
    int cur_time = 0;
    int diff_time = 0;

    int accumulator = 0;

    setbuf(stdout, NULL);

    SDL_TimerID timer_id;

    timer_id = SDL_AddTimer(10,updateComms,&table);


    while(running)
    {
        table.update();
        // Handle events here
        while(SDL_PollEvent(&event))
        {
            // Handle keystrokes here
            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    running = false;
                }
            }
        }


        last_time = cur_time;

    }


//    while (!quit)
//    {
//      printf("Result = %d\n", result);
//    }

        if(table.getNumPlayers() !=0)
          {
            quit =true;
            std::cout<<"num players: "<<table.getNumPlayers()<<"\n";
            std::cout<<"num liveplayers: "<<table.getNumPlayers()<<"\n";
          }

        //table.dealHands();//call gui.dealCardTo(playerID,PlayingCard)

        //table.dealHands(pack);//call gui.dealCardTo(playerID,PlayingCard)


        //table.bet();//internally call gui.receiveBetFrom(playerID,amount)


        //Burning deck card method:
//        GUI::Card* burned = gui.uniqueCard(PlayingCard(Rank::ACE,Suit::SPADE),GUI::LEFT);
//        burned->setFlipped(true,true);
//        burned->setPos(gui.getDeckPos());
//        burned->updateRect();
//        burned->burn();

        //table.dealFlop();//internally call addPublicCard(PlayingCard) x3
        //table.dealFlop();//internally call addPublicCard(PlayingCard) x3


        //table.bet();//internally call gui.receiveBetFrom(playerID,amount)
                        //call gui.receiveBetFrom(playerID,Unit16 amount,bool isFirstBet)
        //table.dealRiverTurn();//internally calladdPublicCard(PlayingCard)
        //table.dealRiverTurn();//internally calladdPublicCard(PlayingCard)

        //table.bet();//internally call gui.receiveBetFrom(playerID,amount)

                        //call gui.receiveBetFrom(playerID,Unit16 amount,bool isFirstBet)


        //table.dealRiverTurn();//internally calladdPublicCard(PlayingCard)
        //table.dealRiverTurn();//internally calladdPublicCard(PlayingCard)

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

