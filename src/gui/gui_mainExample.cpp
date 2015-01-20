#include <math.h>
#include "gui/gui_dealergui.h"

int main()
{
    GUI_DealerGUI gui;

    std::vector<player*> players;

    std::cout<<"Initialising players\n";

    player p1;
    p1.setName(std::string("dick"));
    players.push_back(&p1);
    player p2;
    p2.setName(std::string("butt"));
    players.push_back(&p2);
    player p3;
    p3.setName(std::string("buck"));
    players.push_back(&p3);
    player p4;
    p4.setName(std::string("ditt"));
    players.push_back(&p4);

    std::cout<<"Initialised all players\n";

    PlayingCard aceOfSpades = PlayingCard(Rank::ACE,Suit::SPADE);
//    GUI_Label* testLabel = gui.uniqueLabel(std::string("test"),LEFT);
//    GUI_Card* testCard = gui.uniqueCard(aceOfSpades,LEFT);
    std::vector<PlayingCard> cardList;
    cardList.push_back(aceOfSpades);
    p1.setHandCard(aceOfSpades);
    p2.setHandCard(aceOfSpades);
    p3.setHandCard(aceOfSpades);
    p4.setHandCard(aceOfSpades);
//    cardList.push_back(aceOfSpades);
//    cardList.push_back(aceOfSpades);
//    cardList.push_back(aceOfSpades);
//    cardList.push_back(aceOfSpades);
    //GUI_Hand* testHand = gui.uniqueHand(cardList,BOTTOM);
    std::vector<player*> winningPlayers;
    //winningPlayers.push_back(&p1);
    //winningPlayers.push_back(&p2);
    winningPlayers.push_back(&p3);
    winningPlayers.push_back(&p4);
    Uint16 amount = 100;
//    SDL_Point centre = {160, 128};

    gui.initialise(players, cardList);

    SDL_Event event;
    bool quit=false;

    while (!quit)
    {
        gui.update();
        gui.draw();

        while ( SDL_PollEvent(&event) )
        {
            switch (event.type)
            {
                // this is the window x being clicked.
                case SDL_QUIT : quit = true; break;

                // now we look for a keydown event
                case SDL_KEYDOWN:
                {
                    switch( event.key.keysym.sym )
                    {
                        // if it's the escape key quit
                        case SDLK_ESCAPE :  quit = true; break;

//                        case SDLK_UP : testHand->moveTo(testHand->aligned(TOP));
//                        testLabel->moveTo(testLabel->aligned(BOTTOM));
//                        testCard->moveTo(testCard->aligned(TOP));
//                        break;

//                        case SDLK_RIGHT : testHand->moveTo(testHand->aligned(RIGHT));
//                        testLabel->moveTo(testLabel->aligned(LEFT));
//                        testCard->moveTo(testCard->aligned(RIGHT));
//                        break;

//                        case SDLK_DOWN : testHand->moveTo(testHand->aligned(BOTTOM));
//                        testLabel->moveTo(testLabel->aligned(TOP));
//                        testCard->moveTo(testCard->aligned(BOTTOM));
//                        break;

//                        case SDLK_LEFT : testHand->moveTo(testHand->aligned(LEFT));
//                        testLabel->moveTo(testLabel->aligned(RIGHT));
//                        testCard->moveTo(testCard->aligned(LEFT));
//                        break;

                        //case SDLK_c : testHand->moveTo(gui.getCentre()); /*testCard->moveTo(gui.getCentre());*/ break;
                        case SDLK_PAGEDOWN : gui.m_publicCards->setFlipped(true); break;
                        case SDLK_PAGEUP : gui.m_publicCards->setFlipped(false); break;
                        case SDLK_b : gui.m_publicCards->burn(); break;
                        case SDLK_n : gui.receiveBetFrom(rand()%4,amount); break;
                        case SDLK_v : gui.dealCardTo(rand()%4,aceOfSpades); break;
                        case SDLK_m : gui.broadcastMessage(std::string("Oh hey look a message")); break;
                        case SDLK_t : gui.setPlayerName(0,std::string("dickfuck")); break;
                        case SDLK_z : gui.m_publicCards->addCard(gui.uniqueCard(aceOfSpades,BOTTOM)); break;
                        case SDLK_x : gui.showWinner(winningPlayers); break;
                        case SDLK_r : gui.reset(players,cardList); break;
                        //case SDLK_UP : gui.m_deckCard->setFlipped(true); break;
                        //case SDLK_DOWN : gui.m_deckCard->setFlipped(false); break;
                        default : break;
                    }
                }

                default : break;
            }
        }

        SDL_Delay(32);
    }
    return EXIT_SUCCESS;
}