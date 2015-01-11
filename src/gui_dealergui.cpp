#include "include/gui_dealergui.h"
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <sstream>

#define ONSCREENOFFSET 16
#define OFFSCREENOFFSET 38
#define COOLDOWNTIME 32
#define PIXEL_SCALE 4
#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 256

GUI_DealerGUI::GUI_DealerGUI(const unsigned int &_numPlayers, const GUI_CardInfo *_cardInfo, const GUI_LabelFormat *_labelFormat) :
    //m_publicCards(Hand(SDL_Point(),std::vector<Card>(),BOTTOM)),
    m_renderer(_cardInfo->ren),
    m_maker(GUI_ElementMaker(_cardInfo, _labelFormat)),
    m_numPlayers(_numPlayers)
{
}

GUI_DealerGUI::~GUI_DealerGUI()
{
    //deallocate memory
    //m_elements.clear(); //wait why do we even need this
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void GUI_DealerGUI::initialise()
{
    //-----------------------------------------------------------------------------
    // First thing we need to do is initialise SDL in this case we are
    // setting up just the video subsystem if we need audio or timer etc
    // we would | (or) the flags together see http://www.libsdl.org/intro.en/usinginit.html
    // we check the return value and if not 0 it is an error
    //-----------------------------------------------------------------------------
    if (SDL_Init( SDL_INIT_VIDEO ) !=0)
    {
        SDLErrorExit("error initialising SDL");
    }
    //-----------------------------------------------------------------------------
    // next we create a window and make sure it works
    //-----------------------------------------------------------------------------
    SDL_Window *win = 0;
    win = SDL_CreateWindow("Arduino Poker", 100, 100, WINDOW_WIDTH*PIXEL_SCALE, WINDOW_HEIGHT*PIXEL_SCALE, SDL_WINDOW_SHOWN);
    if (win == 0)
    {
            SDLErrorExit("Error creating Window");
    }
    //-----------------------------------------------------------------------------
    // now we associate a renderer with the window
    //-----------------------------------------------------------------------------
    m_renderer = 0;
    m_renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
    if (!m_renderer)
    {
        SDLErrorExit("error creating renderer");
    }
    SDL_RenderSetLogicalSize(m_renderer,320,256);
    SDL_RenderSetScale(m_renderer,PIXEL_SCALE,PIXEL_SCALE);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    // Initialize SDL_ttf library
    if (TTF_Init() != 0)
    {
        std::cerr << "TTF_Init() Failed: " << TTF_GetError() << "\n";
        SDL_Quit();
        exit(1);
    }

    // Load a font
    TTF_Font *font;
    font = TTF_OpenFont("/home/i7245660/OOPG/IanPoker/fonts/ATARI400800_original.TTF", 8);
    if (!font)
    {
        std::cerr << "TTF_OpenFont() Failed: " << TTF_GetError() << "\n";
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }

    //initialise SDL_image library
    //int imgFlags = IMG_INIT_PNG;
    if (!IMG_Init(IMG_INIT_PNG))
    {
        std::cerr << "IMG_Init() Failed: " << IMG_GetError() << "\n";
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }

    // Load the playing card sheet
    SDL_Surface *temp;
    temp = IMG_Load("/home/i7245660/OOPG/IanPoker/images/sheet_v2.png");
    if (!temp)
    {
        std::cerr << "IMG_Load() Failed: " << IMG_GetError() << "\n";
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }

    //convert it to a texture
    SDL_Texture *cardTexture=SDL_CreateTextureFromSurface(m_renderer,temp);
    if (!cardTexture)
    {
        std::cerr << "SDL_CreateTextureFromSurface() Failed: " << SDL_GetError() << "\n";
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }
    SDL_FreeSurface(temp);

    //set the standard formatting for most of our labels
    const SDL_Color text_color = {255,255,255,255};
    static const GUI_LabelFormat standardFormat = {m_renderer, font, text_color};
    static const GUI_CardInfo cardstyle = {m_renderer, cardTexture, 56, 76};

    m_maker = GUI_ElementMaker(&cardstyle,&standardFormat);

    Uint32 pixelFormat;
    SDL_QueryTexture(cardTexture,&pixelFormat,NULL,NULL,NULL);

    m_renderTarget = SDL_CreateTexture(m_renderer,pixelFormat,SDL_TEXTUREACCESS_TARGET,WINDOW_WIDTH,WINDOW_HEIGHT);

    switch (m_numPlayers)
    {
        case 2 :
            m_players.push_back(createPlayer(1,std::string("Player 1"),BOTTOM,ONSCREENOFFSET));
            m_players.push_back(createPlayer(2,std::string("Player 2"),TOP,ONSCREENOFFSET));
            break;
        case 3 :
            m_players.push_back(createPlayer(1,std::string("Player 1"),BOTTOM,ONSCREENOFFSET));
            m_players.push_back(createPlayer(2,std::string("Player 2"),RIGHT,ONSCREENOFFSET));
            m_players.push_back(createPlayer(3,std::string("Player 3"),TOP,ONSCREENOFFSET));
            break;
        case 4 :
            m_players.push_back(createPlayer(1,std::string("Player 1"),BOTTOM,ONSCREENOFFSET));
            m_players.push_back(createPlayer(2,std::string("Player 2"),RIGHT,ONSCREENOFFSET));
            m_players.push_back(createPlayer(3,std::string("Player 3"),TOP,ONSCREENOFFSET));
            m_players.push_back(createPlayer(4,std::string("Player 4"),LEFT,ONSCREENOFFSET));
            break;
        default :
            std::cout<<"Invalid player count!\n";
            m_players.push_back(createPlayer(1,std::string("You silly bish"),BOTTOM,64));
    }
}

void GUI_DealerGUI::broadcastMessage(const std::string &_message, const unsigned int &_duration)
{
    for (unsigned int i = 0; i < m_players.size(); ++i)
    {
        GUI_Label* messageLabel = uniqueLabel(_message,m_players[i].orient,_duration);
        messageLabel->setPos(m_players[i].pos_offScreen);
        messageLabel->moveTo(m_players[i].pos_onScreen);
    }
}

void GUI_DealerGUI::dealCardTo(const unsigned int &_playerID, const GUI_CardType &_type)
{
    if (_playerID > m_players.size())
    {
        std::cerr<<"ID of non-existent player passed!\n";
        return;
    }

    std::cout<<"Dealing card "<<_type.rank<<" of "<<_type.suit<<" to player "<<_playerID<<"\n";

    GUI_Player thatPlayer = m_players[_playerID];
    boost::shared_ptr<GUI_Element> newCard(m_maker.makeCard(_type, thatPlayer.orient));
    std::cout<<"new card created at "<<&newCard<<"\n";
    m_elements.push_back(newCard);

    newCard->setPos(getCentre());
    newCard->moveTo(thatPlayer.pos_offScreen);
    newCard->kill();
}

void GUI_DealerGUI::receiveBetFrom(const unsigned int &_playerID, Uint16 &_amount, bool _isFirstBet)
{
    if (_playerID > m_players.size())
    {
        std::cerr<<"ID of non-existent player passed!\n";
        return;
    }
    GUI_Player thatPlayer = m_players[_playerID];

    std::cout<<"Receiving bet of $"<<_amount<<" from "<<thatPlayer.name<<"\n";

    std::stringstream amountStream;
    amountStream << _amount;
    std::string betString = std::string("$") + amountStream.str();

    if (_isFirstBet)
    {
        broadcastMessage(thatPlayer.name + std::string(" makes a bet of ") + betString,64);
    }
    else
    {
        broadcastMessage(thatPlayer.name + std::string(" raises the bet to ") + betString,64);
    }

    boost::shared_ptr<GUI_Element> betLabel(m_maker.makeLabel(betString,thatPlayer.orient,32));
    m_elements.push_back(betLabel);

    betLabel->setPos(thatPlayer.pos_offScreen);
    betLabel->moveTo(getCentre());
    betLabel->kill();
}

void GUI_DealerGUI::update()
{
//    for (std::vector< boost::shared_ptr<Element> >::iterator it; it!=m_elements.end(); ++it)
//    {
//        if((*it).get()->shouldKill())
//        {
//            std::cout<<"erasing an element\n";
//            m_elements.erase(it,it);//delete the element; the use of shared_ptr should ensure the memory is cleared up
//        }
//        else
//        {
//            std::cout<<"updating an element\n";
//            (*it).get()->update();
//        }
//    }

    for (int i=0; i<(int)m_elements.size(); ++i)
    {
        if(m_elements[i]->shouldKillNow())
        {
            std::vector< boost::shared_ptr<GUI_Element> >::iterator it = m_elements.begin() + i;
            m_elements.erase(it);//delete the element; the use of shared_ptr should ensure the memory is cleared up
        }
        else
        {
            m_elements[i]->update();
        }
    }

//    if ((int)m_taskQueue.size() >= 1)//if there are any pending tasks
//    {
//        if (m_taskCooldown <= 0)//if enough time has passed since the last one
//        {
//            std::vector< boost::shared_ptr<Task> >::iterator currentTask = m_taskQueue.begin();
//            (*currentTask)->execute();
//            m_taskQueue.erase(currentTask);
//            m_taskCooldown = COOLDOWNTIME;
//        }
//        else
//        {
//            --m_taskCooldown;
//        }
//    }
}

void GUI_DealerGUI::draw()
{
    SDL_SetRenderTarget(m_renderer, m_renderTarget);
    clearScreen(m_renderer,2,180,2);

//    for (std::vector< boost::shared_ptr<Element> >::iterator it; it!=m_elements.end(); ++it)
//    {
//        (*it)->draw();
//    }

    for (int i=0; i<(int)m_elements.size(); ++i)
    {
            m_elements[i]->draw();
    }

    SDL_SetRenderTarget(m_renderer, NULL);
    SDL_RenderCopy(m_renderer,m_renderTarget,NULL,NULL);

    // finally we need to tell SDL to update the screen
    SDL_RenderPresent(m_renderer);
}

GUI_Player GUI_DealerGUI::createPlayer(const Uint8 &_id, const std::string &_name, const GUI_Orientation &_orient, const int _offset)
{
    //onScreen is the position where this player's public items will be drawn
    //offScreen is where items will be moved to make it look like they are being given to this player
    //_offset is how far from this player's side of the screen the onScreen position will be
    SDL_Point screen = getScreenDimensions();
    SDL_Point half = getCentre();
    //std::cout<<"CreatePlayer width: "<<screen.x<<" CreatePlayer height: "<<screen.y<<"\n";
    SDL_Point onScreen, offScreen;

    switch(_orient)
    {
        case BOTTOM :
            onScreen.x = half.x;
            offScreen.x = half.x;
            onScreen.y = screen.y - _offset;
            offScreen.y = screen.y + OFFSCREENOFFSET;
            break;

        case TOP :
            onScreen.x = half.x;
            offScreen.x = half.x;
            onScreen.y = _offset;
            offScreen.y = -OFFSCREENOFFSET;
            break;

        case LEFT :
            onScreen.x = _offset;
            offScreen.x = -OFFSCREENOFFSET;
            onScreen.y = half.y;
            offScreen.y = half.y;
            break;

        case RIGHT :
            onScreen.x = screen.x - _offset;
            offScreen.x = screen.x + OFFSCREENOFFSET;
            onScreen.y = half.y;
            offScreen.y = half.y;
            break;

        default :
            onScreen = half;
            offScreen = half;
    }

//    std::cout<<_name<<"'s off-screen position at ("<<offScreen.x<<", "<<offScreen.y<<")\n";

    boost::shared_ptr<GUI_Label> playerLabel(m_maker.makeLabel(_name,_orient,0));
    GUI_Label* labelPtr = playerLabel.get();
    m_elements.push_back(playerLabel);

    //move it into a corner
    labelPtr->setPos(getCentre());
    labelPtr->setPos(labelPtr->aligned(_orient));
    labelPtr->updateRect();

    GUI_Player temp = {_id, onScreen, offScreen, _name, _orient, labelPtr};
//    std::cout<<"label position: ";
//    labelPtr->printRect();
    return temp;
}

SDL_Point GUI_DealerGUI::getScreenDimensions()
{
    SDL_Point temp;
    SDL_RenderGetLogicalSize(m_renderer,&temp.x,&temp.y);
    //std::cout<<"Screen width: "<<temp.x<<" Screen height: "<<temp.y<<"\n";
    return temp;
}

SDL_Point GUI_DealerGUI::getCentre()
{
    SDL_Point temp = getScreenDimensions();
    temp.x /= 2;
    temp.y /= 2;
    return temp;
}

GUI_Card* GUI_DealerGUI::uniqueCard(const GUI_CardType &_type, const unsigned int &_playerID)
{
    boost::shared_ptr<GUI_Card> temp(m_maker.makeCard(_type,m_players[_playerID].orient));
    m_elements.push_back(temp);
    return temp.get();
}

GUI_Card* GUI_DealerGUI::uniqueCard(const GUI_CardType &_type, const GUI_Orientation &_orient)
{
    boost::shared_ptr<GUI_Card> temp(m_maker.makeCard(_type,_orient));
    m_elements.push_back(temp);
    return temp.get();
}

GUI_Label* GUI_DealerGUI::uniqueLabel(const std::string &_inputString, const unsigned int &_playerID, const int &_lifetime)
{
    boost::shared_ptr<GUI_Label> temp(m_maker.makeLabel(_inputString,m_players[_playerID].orient,_lifetime));
    m_elements.push_back(temp);
    return temp.get();
}

GUI_Label* GUI_DealerGUI::uniqueLabel(const std::string &_inputString, const GUI_Orientation &_orient, const int &_lifetime)
{
    boost::shared_ptr<GUI_Label> temp(m_maker.makeLabel(_inputString,_orient,_lifetime));
    m_elements.push_back(temp);
    return temp.get();
}

GUI_Hand GUI_DealerGUI::uniqueHand(const std::vector<GUI_CardType> &_cards, const unsigned int &_playerID)
{
    std::vector<GUI_Card*> handCards;
    for (std::vector<GUI_CardType>::const_iterator it = _cards.begin(); it != _cards.end(); ++it)
    {
        boost::shared_ptr<GUI_Card> temp(m_maker.makeCard((*it),m_players[_playerID].orient));
        m_elements.push_back(temp);
        handCards.push_back(temp.get());
    }
    return GUI_Hand(handCards,m_players[_playerID].orient);
}

GUI_Hand GUI_DealerGUI::uniqueHand(const std::vector<GUI_CardType> &_cards, const GUI_Orientation &_orient)
{
    std::vector<GUI_Card*> handCards;
    for (std::vector<GUI_CardType>::const_iterator it = _cards.begin(); it != _cards.end(); ++it)
    {
        boost::shared_ptr<GUI_Card> temp(m_maker.makeCard((*it),_orient));
        m_elements.push_back(temp);
        handCards.push_back(temp.get());
    }
    return GUI_Hand(handCards,_orient);
}

void GUI_DealerGUI::SDLErrorExit(const std::string &_msg)
{
  std::cerr<<_msg<<"\n";
  std::cerr<<SDL_GetError()<<"\n";
  SDL_Quit();
  exit(EXIT_FAILURE);
}

void GUI_DealerGUI::clearScreen(SDL_Renderer *_ren,char _r,char _g,char _b	)
{
    SDL_SetRenderDrawColor(_ren, _r,_g,_b,255);
    SDL_RenderClear(_ren);
}

void GUI_DealerGUI::setPlayerName(const unsigned int &_id, std::string _name)
{
    m_players[_id].name = _name;
    m_players[_id].nameLabel->killNow();

    boost::shared_ptr<GUI_Label> playerLabel(m_maker.makeLabel(_name,m_players[_id].orient,0));
    GUI_Label* labelPtr = playerLabel.get();
    m_elements.push_back(playerLabel);

    //move it into a corner
    labelPtr->setPos(getCentre());
    labelPtr->setPos(labelPtr->aligned(m_players[_id].orient));
    labelPtr->updateRect();

    m_players[_id].nameLabel = labelPtr;
}
