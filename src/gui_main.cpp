#include "gui_dealergui.h"
#include <math.h>

int main()
{
    GUI_CardInfo cardInfo = GUI_CardInfo();
    GUI_LabelFormat labelFormat = GUI_LabelFormat();
    GUI_DealerGUI gui(4);
    gui.initialise();

    PlayingCard aceOfSpades = PlayingCard(Rank::TWO,Suit::HEART);
//    GUI_Label* testLabel = gui.uniqueLabel(std::string("test"),LEFT);
//    GUI_Card* testCard = gui.uniqueCard(aceOfSpades,LEFT);
    std::vector<PlayingCard> cardList;
    cardList.push_back(aceOfSpades);
//    cardList.push_back(aceOfSpades);
//    cardList.push_back(aceOfSpades);
//    cardList.push_back(aceOfSpades);
//    cardList.push_back(aceOfSpades);
    GUI_Hand testHand = gui.uniqueHand(cardList,BOTTOM);
    Uint16 amount = 100;
//    SDL_Point centre = {160, 128};

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

                        case SDLK_UP : testHand.moveTo(testHand.aligned(TOP));
//                        testLabel->moveTo(testLabel->aligned(BOTTOM));
//                        testCard->moveTo(testCard->aligned(TOP));
                        break;

                        case SDLK_RIGHT : testHand.moveTo(testHand.aligned(RIGHT));
//                        testLabel->moveTo(testLabel->aligned(LEFT));
//                        testCard->moveTo(testCard->aligned(RIGHT));
                        break;

                        case SDLK_DOWN : testHand.moveTo(testHand.aligned(BOTTOM));
//                        testLabel->moveTo(testLabel->aligned(TOP));
//                        testCard->moveTo(testCard->aligned(BOTTOM));
                        break;

                        case SDLK_LEFT : testHand.moveTo(testHand.aligned(LEFT));
//                        testLabel->moveTo(testLabel->aligned(RIGHT));
//                        testCard->moveTo(testCard->aligned(LEFT));
                        break;

                        case SDLK_c : testHand.moveTo(gui.getCentre()); /*testCard->moveTo(gui.getCentre());*/ break;
//                        case SDLK_PAGEDOWN : testHand.setFlipped(true); break;
//                        case SDLK_PAGEUP : testHand.setFlipped(false); break;
                        case SDLK_b : testHand.burn(); break;
                        case SDLK_n : gui.receiveBetFrom(rand()%4,amount); break;
                        case SDLK_v : gui.dealCardTo(rand()%4,aceOfSpades); break;
                        case SDLK_m : gui.broadcastMessage(std::string("Oh hey look a message")); break;
                        case SDLK_x : gui.setPlayerName(0,std::string("dickbutt")); break;
                        case SDLK_z : testHand.addCard(gui.uniqueCard(aceOfSpades,BOTTOM)); break;
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
