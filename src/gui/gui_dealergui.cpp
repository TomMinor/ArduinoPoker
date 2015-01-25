#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <sstream>
#include <cstdlib>

#include "include/gui/gui_dealergui.h"

#define ONSCREENOFFSET 48
#define OFFSCREENOFFSET 38
#define COOLDOWNTIME 32
#define PIXEL_SCALE 3
#define WINDOW_WIDTH 480
#define WINDOW_HEIGHT 360

#define BORDER_CORNERWIDTH 120
#define BORDER_IMGWIDTH 470
#define BORDER_FILLERWIDTH 8
#define BORDER_LINEWIDTH 15

GUI::DealerGUI::DealerGUI() :
    //m_publicCards(Hand(SDL_Point(),std::vector<Card>(),BOTTOM)),
    m_renderer(NULL),
    m_maker(GUI::ElementMaker(NULL, NULL)),
    m_elements(std::vector< boost::shared_ptr<GUI::Element> >())
{
//    SDL_Point origin = {0,0};
//    GUI::Player temp;
//    temp.nameLabel = NULL;
//    temp.orient = BOTTOM;
//    temp.playerClass = _players[0];
//    temp.pos_offScreen = origin;
//    temp.pos_onScreen = origin;
//    temp.nameLabel = uniqueLabel(_players[0]->getName());
//    temp.nameLabel->setPos(getCentre());
//    temp.nameLabel->setPos(temp.nameLabel->aligned(BOTTOM));
//    temp.nameLabel->updateRect();

//    m_players.push_back(temp);
//    temp.playerClass = _players[1];
//    temp.orient = TOP;
//    temp.nameLabel = uniqueLabel(_players[1]->getName());
//    temp.nameLabel->setPos(getCentre());
//    temp.nameLabel->setPos(temp.nameLabel->aligned(TOP));
//    temp.nameLabel->updateRect();
//    m_players.push_back(temp);

//    std::cout<<"Player 1 orient: "<<static_cast<int>(m_players[0].orient)<<"\n";
//    std::cout<<"Player 2 orient: "<<static_cast<int>(m_players[1].orient)<<"\n";
}

GUI::DealerGUI::~DealerGUI()
{
    //deallocate memory
    //m_elements.clear(); //wait why do we even need this
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void GUI::DealerGUI::initialise(std::vector<const player *> _players,
                                const std::vector<PlayingCard> &_publicCards,
                                const unsigned int &_windowWidth,
                                const unsigned int &_windowHeight,
                                const unsigned int &_pixelScale)
{
    //-----------------------------------------------------------------------------
    // First thing we need to do is initialise SDL in this case we are
    // setting up just the video subsystem if we need audio or timer etc
    // we would | (or) the flags together see http://www.libsdl.org/intro.en/usinginit.html
    // we check the return value and if not 0 it is an error
    //-----------------------------------------------------------------------------
    if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) !=0)
    {
        SDLErrorExit("error initialising SDL");
    }
    //-----------------------------------------------------------------------------
    // next we create a window and make sure it works
    //-----------------------------------------------------------------------------
    SDL_Window *win = 0;
    win = SDL_CreateWindow("Arduino™ Poker Simulator 1992", 100, 100, _windowWidth*_pixelScale, _windowHeight*_pixelScale, SDL_WINDOW_SHOWN);
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
    SDL_RenderSetLogicalSize(m_renderer,_windowWidth,_windowHeight);
    SDL_RenderSetScale(m_renderer,_pixelScale,_pixelScale);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    // Initialize SDL_ttf library
    if (TTF_Init() != 0)
    {
        std::cerr << "TTF_Init() Failed: " << TTF_GetError() << "\n";
        SDL_Quit();
        exit(1);
    }

    //get our directory
    const size_t bufsize = 128;
    char buf[bufsize] = "";
    readlink("/proc/self/exe",buf,bufsize);
    std::string ourDir = std::string(buf);
    ourDir = ourDir.substr(0, ourDir.size()-9);

    // Load a font
    TTF_Font *font;
//    font = TTF_OpenFont("/home/i7245660/OOPG/IanPoker/fonts/ATARI400800_original.TTF", 8);
//    font = TTF_OpenFont("/home/i7245143/OS/Software_Engineering/IanPoker/fonts/ATARI400800_original.TTF", 8);
    font = TTF_OpenFont((ourDir + std::string("fonts/ATARI400800_original.TTF")).c_str(), 8);
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
//    temp = IMG_Load("/home/i7245660/OOPG/IanPoker/images/sheet_v3.png");
    temp = IMG_Load((ourDir + std::string("images/sheet_v3.png")).c_str());
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
    static const GUI::LabelFormat standardFormat = {m_renderer, font, text_color};
    static const GUI::CardInfo cardstyle = {m_renderer, cardTexture, 56, 76};

    m_maker = GUI::ElementMaker(&cardstyle,&standardFormat);

    Uint32 pixelFormat;
    SDL_QueryTexture(cardTexture,&pixelFormat,NULL,NULL,NULL);

    m_renderTarget = SDL_CreateTexture(m_renderer,pixelFormat,SDL_TEXTUREACCESS_TARGET,_windowWidth,_windowHeight);

    setUpUniqueElements(_publicCards,_players.size());
    setUpPlayers(_players);
    std::cout<<"are we here?\n\n";

}

void GUI::DealerGUI::broadcastMessage(const std::string &_message, const unsigned int &_duration)
{
    for (std::vector<Label*>::iterator it = m_activeMessages.begin(); it != m_activeMessages.end(); ++it)
    {
        (*it)->killNow();
    }
    m_activeMessages.clear();

    for (unsigned int i = 0; i < m_players.size(); ++i)
    {
        GUI::Label* messageLabel = uniqueLabel(_message,m_players[i].orient,_duration);
        std::cout<<"Broadcasting message: \""<<_message<<"\"\n";
        m_activeMessages.push_back(messageLabel);
        messageLabel->setPos(m_players[i].pos_offScreen);
        messageLabel->moveTo(m_players[i].pos_onScreen);
    }
    std::cout<<"Broadcasting message: \""<<_message<<"\"\n";
}

void GUI::DealerGUI::dealCardTo(const unsigned int &_playerID, const PlayingCard &_type)
{
    if (_playerID > m_players.size())
    {
        std::cerr<<"ID of non-existent player passed!\n";
        return;
    }

    GUI::Player* thatPlayer = &m_players[_playerID];

    std::cout<<"Dealing card "<<_type.getRank()<<" of "<<_type.getSuit()<<" to player "<<_playerID<<"\n";

    Card* newCard = uniqueCard(_type,thatPlayer->orient);

    SDL_Point destination = thatPlayer->pos_offScreen;
    if (thatPlayer->orient == TOP || thatPlayer->orient == BOTTOM)
    {
        destination.x += rand()%128;
        destination.x -= 64;
    }
    else
    {
        destination.y += rand()%128;
        destination.y -= 64;
    }

    newCard->setPos(m_deckPos);
    newCard->setFlipped(true,true);
    newCard->moveTo(destination);
    newCard->kill();
}

void GUI::DealerGUI::receiveBetFrom(const unsigned int &_playerID, Uint16 &_amount, bool _isFirstBet)
{
    if (_playerID > m_players.size())
    {
        std::cerr<<"ID of non-existent player passed!\n";
        return;
    }
    GUI::Player* thatPlayer = &m_players[_playerID];

    std::cout<<"Receiving bet of $"<<_amount<<" from "<<thatPlayer->playerClass->getName()<<"\n";

    std::stringstream amountStream;
    amountStream << _amount;
    std::string betString = std::string("$") + amountStream.str();
    std::cout<<"before possible danger: "<<betString<<"\n";

    if (_isFirstBet)
    {
        broadcastMessage(thatPlayer->playerClass->getName() + std::string(" makes a bet of ") + betString,64);
    }
    else
    {
        broadcastMessage(thatPlayer->playerClass->getName() + std::string(" raises the bet to ") + betString,64);
    }

    GUI::Label* betLabel = uniqueLabel(betString,thatPlayer->orient,32);

    SDL_Point thatPoint = m_potPos;
    switch (thatPlayer->orient)
    {
        case TOP: thatPoint.y -= 48;    break;
        case BOTTOM: thatPoint.y += 48; break;
        case LEFT: thatPoint.x -= 48;   break;
        case RIGHT: thatPoint.x += 48;  break;
    }

    betLabel->setPos(thatPlayer->pos_offScreen);
    betLabel->moveTo(thatPoint);
    betLabel->kill();

    if ((m_pot->getPos().x != m_potPos.x) && (m_pot->getPos().y != m_potPos.y))
    {
        m_pot->setPos(thatPlayer->pos_offScreen);
        m_pot->moveTo(m_potPos);
    }
}

void GUI::DealerGUI::runUntilStationary()
{
    while (update())
    {
        draw();
        SDL_Delay(32);
    }
    draw();
}

bool GUI::DealerGUI::update()
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

    bool returnThis = false;

    for (int i=0; i<(int)m_elements.size(); ++i)
    {
        if(m_elements[i]->shouldKillNow())
        {
            std::vector< boost::shared_ptr<GUI::Element> >::iterator it = m_elements.begin() + i;
            m_elements.erase(it);//delete the element; the use of shared_ptr should ensure the memory is cleared up
        }
        else
        {
            bool hi = m_elements[i]->update();
            returnThis = returnThis || hi;
        }
    }
    return returnThis;

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

void GUI::DealerGUI::draw()
{
    SDL_SetRenderTarget(m_renderer, m_renderTarget);

    clearScreen(2,180,2);

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

GUI::Player GUI::DealerGUI::createPlayer(const player *_playerRef, const GUI::Orientation &_orient, const int _offset)
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

    GUI::Label* labelPtr = uniqueLabel(_playerRef->getName(),_orient);

    //move it into a corner
    labelPtr->centre(true);
    labelPtr->align(_orient,true);
    SDL_Point newPos = labelPtr->getPos();
    switch (_orient)
    {
        case BOTTOM : newPos.y -= 10; break;
        case TOP    : newPos.y += 10; break;
        case LEFT   : newPos.x += 10; break;
        case RIGHT  : newPos.x -= 10; break;
    }

    labelPtr->setPos(newPos);
    //labelPtr->setPos(labelPtr->aligned(_orient));
    labelPtr->updateRect();

    GUI::Player temp = {_playerRef, onScreen, offScreen, _orient, labelPtr};
//    std::cout<<"label position: ";
//    labelPtr->printRect();
    return temp;
}

void GUI::DealerGUI::setPlayerName(const unsigned int &_playerID, std::string _name)
{
    GUI::Player* thatPlayer = &m_players[_playerID];
    thatPlayer->nameLabel->killNow();
    GUI::Label* newLabel = uniqueLabel(_name,thatPlayer->orient);
    newLabel->setPos(getCentre());
    newLabel->setPos(newLabel->aligned(thatPlayer->orient));

    SDL_Point newPos = newLabel->getPos();
    switch (thatPlayer->orient)
    {
        case BOTTOM : newPos.y -= 10; break;
        case TOP    : newPos.y += 10; break;
        case LEFT   : newPos.x += 10; break;
        case RIGHT  : newPos.x -= 10; break;
    }

    newLabel->setPos(newPos);
    newLabel->updateRect();

    thatPlayer->nameLabel = newLabel;
}

SDL_Point GUI::DealerGUI::getScreenDimensions()
{
    SDL_Point temp;
    SDL_RenderGetLogicalSize(m_renderer,&temp.x,&temp.y);
    //std::cout<<"Screen width: "<<temp.x<<" Screen height: "<<temp.y<<"\n";
    return temp;
}

SDL_Point GUI::DealerGUI::getCentre()
{
    SDL_Point temp = getScreenDimensions();
    temp.x /= 2;
    temp.y /= 2;
    return temp;
}

GUI::Card* GUI::DealerGUI::uniqueCard(const PlayingCard &_type, const unsigned int &_playerID)
{
    boost::shared_ptr<GUI::Card> temp(m_maker.makeCard(_type,m_players[_playerID].orient));
    m_elements.push_back(temp);
    return temp.get();
}

GUI::Card* GUI::DealerGUI::uniqueCard(const PlayingCard &_type, const GUI::Orientation &_orient)
{
    boost::shared_ptr<GUI::Card> temp(m_maker.makeCard(_type,_orient));
    m_elements.push_back(temp);
    return temp.get();
}

GUI::Label* GUI::DealerGUI::uniqueLabel(const std::string &_inputString, const unsigned int &_playerID, const int &_lifetime)
{
    boost::shared_ptr<GUI::Label> temp(m_maker.makeLabel(_inputString,m_players[_playerID].orient,_lifetime));
    m_elements.push_back(temp);
    return temp.get();
}

GUI::Label* GUI::DealerGUI::uniqueLabel(const std::string &_inputString, const GUI::Orientation &_orient, const int &_lifetime)
{
    boost::shared_ptr<GUI::Label> temp(m_maker.makeLabel(_inputString,_orient,_lifetime));
    m_elements.push_back(temp);
     return temp.get();
}

GUI::Hand* GUI::DealerGUI::uniqueHand(const std::vector<PlayingCard> &_cards, const unsigned int &_playerID)
{
    std::vector<GUI::Card*> handCards;
    for (std::vector<PlayingCard>::const_iterator it = _cards.begin(); it != _cards.end(); ++it)
    {
        boost::shared_ptr<GUI::Card> temp(m_maker.makeCard((*it),m_players[_playerID].orient));
        m_elements.push_back(temp);
        handCards.push_back(temp.get());
    }
    boost::shared_ptr<GUI::Hand> temp(new GUI::Hand(handCards,m_players[_playerID].orient));
    m_hands.push_back(temp);
    return temp.get();
}

GUI::Hand* GUI::DealerGUI::uniqueHand(const std::vector<PlayingCard> &_cards, const GUI::Orientation &_orient)
{
    std::vector<GUI::Card*> handCards;
    for (std::vector<PlayingCard>::const_iterator it = _cards.begin(); it != _cards.end(); ++it)
    {
        boost::shared_ptr<GUI::Card> temp(m_maker.makeCard((*it),_orient));
        m_elements.push_back(temp);
        handCards.push_back(temp.get());
    }
    boost::shared_ptr<GUI::Hand> temp(new GUI::Hand(handCards,_orient));
    m_hands.push_back(temp);
    return temp.get();
}

GUI::Element* GUI::DealerGUI::uniqueElement(SDL_Texture *_tex, const GUI::Orientation &_orient)
{
    boost::shared_ptr<GUI::Element> temp(m_maker.makeElement(_tex,_orient));
    m_elements.push_back(temp);
    return temp.get();
}

GUI::Element* GUI::DealerGUI::uniqueElement(SDL_Texture* _tex, const SDL_Rect &_srcRect, const SDL_Rect &_destRect, const Orientation &_orient)
{
    boost::shared_ptr<GUI::Element> temp(m_maker.makeElement(_tex,_srcRect,_destRect,_orient));
    m_elements.push_back(temp);
    return temp.get();
}

GUI::Element* GUI::DealerGUI::uniqueElement(Element* _inputElement)
{
    boost::shared_ptr<GUI::Element> temp(m_maker.makeElement(_inputElement));
    m_elements.push_back(temp);
    return temp.get();
}

void GUI::DealerGUI::SDLErrorExit(const std::string &_msg)
{
  std::cerr<<_msg<<"\n";
  std::cerr<<SDL_GetError()<<"\n";
  SDL_Quit();
  exit(EXIT_FAILURE);
}

void GUI::DealerGUI::clearScreen(Uint8 _r, Uint8 _g, Uint8 _b	)
{
    SDL_SetRenderDrawColor(m_renderer, _r,_g,_b,255);
    SDL_RenderClear(m_renderer);
}

//void GUI::DealerGUI::setPlayerName(const unsigned int &_playerID, std::string _name)
//{
//    m_players[_playerID].name = _name;
//    m_players[_playerID].nameLabel->killNow();

//    boost::shared_ptr<GUI::Label> playerLabel(m_maker.makeLabel(_name,m_players[_playerID].orient,0));
//    GUI::Label* labelPtr = playerLabel.get();
//    m_elements.push_back(playerLabel);

//    //move it into a corner
//    labelPtr->setPos(getCentre());
//    labelPtr->setPos(labelPtr->aligned(m_players[_playerID].orient));
//    labelPtr->updateRect();

//    m_players[_playerID].nameLabel = labelPtr;
//}

//GUI::CardType GUI::DealerGUI::convert(const PlayingCard &_card)
//{
//    GUI::CardType temp;

//    switch (_card.getRank())
//    {
//        case ACE    : temp.rank = ACE;      break;
//        case TWO    : temp.rank = TWO;      break;
//        case THREE  : temp.rank = THREE;    break;
//        case FOUR   : temp.rank = FOUR;     break;
//        case FIVE   : temp.rank = FIVE;     break;
//        case SIX    : temp.rank = SIX;      break;
//        case SEVEN  : temp.rank = SEVEN;    break;
//        case EIGHT  : temp.rank = EIGHT;    break;
//        case NINE   : temp.rank = NINE;     break;
//        case TEN    : temp.rank = TEN;      break;
//        case JACK   : temp.rank = JACK;     break;
//        case QUEEN  : temp.rank = QUEEN;    break;
//        case KING   : temp.rank = KING;     break;
//        default     : temp.rank = ACE;      break;
//    }

//    switch (_card.getSuit())
//    {
//        case Suit::CLUB     : temp.suit = CLUBS;    break;
//        case Suit::SPADE    : temp.suit = SPADES;   break;
//        case Suit::DIAMOND  : temp.suit = DIAMONDS; break;
//        case Suit::HEART    : temp.suit = HEARTS;   break;
//        default             : temp.suit = SPADES;   break;
//    }

//    return temp;
//}

//GUI::Hand GUI::DealerGUI::convert(const std::vector<PlayingCard> &_cards)
//{
//    std::vector<PlayingCard> handCards;
//    for (std::vector<PlayingCard>::iterator it; it !=_cards.end(); ++it)
//    {
//        handCards.push_back((*it));
//    }
//    return uniqueHand(handCards,BOTTOM);
//}

std::vector<GUI::Hand*> GUI::DealerGUI::showWinner(const std::vector<unsigned int> &_winnerIDs, const bool &_hasRemainder, const unsigned int &_winnings)
{
    splitPot(_winnerIDs,_hasRemainder);

    std::vector<GUI::Hand*> winningHands;
    SDL_Point current = getCentre();
    current.y -= _winnerIDs.size() * 38;
    current.y += 38;

    std::stringstream moneyStream;
    moneyStream << _winnings;
    std::string moneyString = std::string("$") + moneyStream.str();

    if (_winnerIDs.size() == 1)
    {
        broadcastMessage(m_players[_winnerIDs[0]].playerClass->getName() + std::string(" wins ") + moneyString + std::string("! Here is their hand."));
    }
    else if (_winnerIDs.size() >= 1)
    {
        std::string message("");
        for (unsigned long i = 0; i < _winnerIDs.size()-1; i++)
        {
            message += m_players[_winnerIDs[i]].playerClass->getName();
            if (_winnerIDs.size() != 2)
            {
                message += std::string(", ");
            }
            else
            {
                message += std::string(" ");
            }
        }

        message += std::string("and ") + m_players[_winnerIDs.back()].playerClass->getName() + std::string(" each win ") + moneyString + std::string("!");
        broadcastMessage(message);
    }
    else
    {
        std::cerr<<"No players passed to GUI showWinners function!\n";
        return std::vector<GUI::Hand*>();
    }

    for (std::vector<unsigned int>::const_iterator it = _winnerIDs.begin(); it != _winnerIDs.end(); ++it)
    {
        GUI::Hand* thisHand = uniqueHand(m_players[(*it)].playerClass->getHand());
        thisHand->setPos(m_players[(*it)].pos_offScreen);
        thisHand->moveTo(current);
        current.y += thisHand->getHeight();
        winningHands.push_back(thisHand);
    }

    return winningHands;
}

void GUI::DealerGUI::reset(std::vector<const player*> _players, std::vector<PlayingCard> _publicCards)
{
    m_hands.clear();
    m_elements.clear();
    setUpUniqueElements(_publicCards, _players.size());
    setUpPlayers(_players);
}

void GUI::DealerGUI::setUpPlayers(std::vector<const player *> _players)
{
    switch (_players.size())
    {
        case 2 :
            m_players.push_back(createPlayer(_players[0],BOTTOM,ONSCREENOFFSET));
            m_players.push_back(createPlayer(_players[1],TOP,ONSCREENOFFSET));
            break;
        case 3 :
            m_players.push_back(createPlayer(_players[0],BOTTOM,ONSCREENOFFSET));
            m_players.push_back(createPlayer(_players[1],RIGHT,ONSCREENOFFSET));
            m_players.push_back(createPlayer(_players[2],TOP,ONSCREENOFFSET));
            break;
        case 4 :
            m_players.push_back(createPlayer(_players[0],BOTTOM,ONSCREENOFFSET));
            m_players.push_back(createPlayer(_players[1],RIGHT,ONSCREENOFFSET));
            m_players.push_back(createPlayer(_players[2],TOP,ONSCREENOFFSET));
            m_players.push_back(createPlayer(_players[3],LEFT,ONSCREENOFFSET));
            break;
        default :
            std::cout<<"Invalid player count!\n";
            //m_players.push_back(createPlayer(1,std::string("You silly bish"),BOTTOM,64));
    }
}

void GUI::DealerGUI::setUpUniqueElements(std::vector<PlayingCard> _publicCards, const unsigned int &_numPlayers)
{
    //get our directory
    const size_t bufsize = 128;
    char buf[bufsize] = "";
    readlink("/proc/self/exe",buf,bufsize);
    std::string ourDir = std::string(buf);
    ourDir = ourDir.substr(0, ourDir.size()-9);

    // Load the pot image
    SDL_Surface *temp;
    //temp = IMG_Load("/home/i7245660/OOPG/IanPoker/images/pot.png");
    temp = IMG_Load((ourDir + std::string("images/pot.png")).c_str());
    if (!temp)
    {
        std::cerr << "IMG_Load() Failed: " << IMG_GetError() << "\n";
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }

    //convert it to a texture
    SDL_Texture *potTexture=SDL_CreateTextureFromSurface(m_renderer,temp);
    if (!potTexture)
    {
        std::cerr << "SDL_CreateTextureFromSurface() Failed: " << SDL_GetError() << "\n";
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }

    // Load the border image
    //temp = IMG_Load("/home/i7245660/OOPG/IanPoker/images/pot.png");
    temp = IMG_Load((ourDir + std::string("images/AWTborder.png")).c_str());
    if (!temp)
    {
        std::cerr << "IMG_Load() Failed: " << IMG_GetError() << "\n";
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }

    //convert it to a texture
    SDL_Texture *borderTexture=SDL_CreateTextureFromSurface(m_renderer,temp);
    if (!borderTexture)
    {
        std::cerr << "SDL_CreateTextureFromSurface() Failed: " << SDL_GetError() << "\n";
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }

    SDL_FreeSurface(temp);

    setUpBorder(borderTexture,_numPlayers);

    SDL_Point position = getCentre();
    position.y -= 48;

    m_publicCards = uniqueHand(_publicCards,BOTTOM);
    //m_publicCards->setFlipped(true);
    m_publicCards->moveTo(position);

    position.y += 96;
    position.x -= 64;
    m_deckPos = position;
    position.x += 128;
    m_potPos = position;

    m_pot = uniqueElement(potTexture);
    SDL_Point offScreen = {-128, -128};
    m_pot->setPos(offScreen);
    m_pot->updateRect();

    GUI::Card* deckCard = uniqueCard(PlayingCard((card_t)1),LEFT);
    deckCard->setFlipped(true,true);
    deckCard->setPos(m_deckPos);
    deckCard->updateRect();
}

void GUI::DealerGUI::addPublicCard(const PlayingCard &_type)
{
    GUI::Card* newCard = uniqueCard(_type,BOTTOM);
    newCard->setPos(m_deckPos);
    newCard->setFlipped(true,true);
    newCard->setFlipped(false);
    m_publicCards->addCard(newCard);
}

void GUI::DealerGUI::kickPlayer(const unsigned int &_playerID, const unsigned int &_money)
{
    GUI::Player* thatPlayer = &m_players[_playerID];
    sendNameAway(_playerID);
    broadcastMessage(thatPlayer->playerClass->getName() + std::string(" has been kicked for this round"));

    std::stringstream amountStream;
    amountStream << _money;
    std::string betString = std::string("$") + amountStream.str();

    GUI::Label* betLabel = uniqueLabel(betString, thatPlayer->orient, 32);

    SDL_Point thisPoint = m_potPos;
    switch (thatPlayer->orient)
    {
        case TOP: thisPoint.y -= 48;    break;
        case BOTTOM: thisPoint.y += 48; break;
        case LEFT: thisPoint.x -= 48;   break;
        case RIGHT: thisPoint.x += 48;  break;
    }

    betLabel->setPos(thisPoint);
    betLabel->moveTo(thatPlayer->pos_offScreen);
    betLabel->kill();
}

void GUI::DealerGUI::addPlayerBack(const unsigned int &_playerID)
{
    bringNameBack(_playerID);
    broadcastMessage(m_players[_playerID].playerClass->getName() + std::string(" is back in play"));
}

void GUI::DealerGUI::setUpBorder(SDL_Texture *_tex, const unsigned int &_numPlayers)
{
    //FYI, all this complex code is necessary to make the borders resolution-independent
    SDL_Point bounds = getScreenDimensions();
    SDL_Rect src, dest;

    //==================== Fillers ====================

    if (getScreenDimensions().x > 2 * BORDER_CORNERWIDTH)
    {
        src.h = BORDER_LINEWIDTH;
        src.w = BORDER_FILLERWIDTH;
        src.x = BORDER_CORNERWIDTH - BORDER_FILLERWIDTH;
        src.y = 0;

        dest.h = BORDER_LINEWIDTH;
        dest.w = bounds.x;
        dest.x = 0;
        dest.y = 0;

        GUI::Element* topFiller = uniqueElement(_tex,src,dest);
        topFiller->centre(true,false);
        topFiller->align(TOP,true,false);

        src.y = BORDER_IMGWIDTH - BORDER_LINEWIDTH;
        dest.y = bounds.y - src.h;
        GUI::Element* bottomFiller = uniqueElement(_tex,src,dest);
        bottomFiller->centre(true,false);
        bottomFiller->align(TOP,true,false);
    }

    if (getScreenDimensions().y > 2 * BORDER_CORNERWIDTH)
    {
        src.h = BORDER_FILLERWIDTH;
        src.w = BORDER_LINEWIDTH;
        src.x = 0;
        src.y = BORDER_CORNERWIDTH - BORDER_FILLERWIDTH;

        dest.h = bounds.y;
        dest.w = BORDER_LINEWIDTH;
        dest.x = 0;
        dest.y = 0;

        GUI::Element* leftFiller = uniqueElement(_tex,src,dest);
        leftFiller->centre(true,false);
        leftFiller->align(LEFT,true,false);

        src.x = BORDER_IMGWIDTH - BORDER_LINEWIDTH;
        dest.x = bounds.x - src.w;
        GUI::Element* rightFiller = uniqueElement(_tex,src,dest);
        rightFiller->centre(true,false);
        rightFiller->align(RIGHT,true,false);
    }

    //==================== Corners ====================

    src.h = BORDER_CORNERWIDTH;
    src.w = BORDER_CORNERWIDTH;
    src.x = 0;
    src.y = 0;

    dest = src;

    GUI::Element* topLeft = uniqueElement(_tex,src,dest);
    topLeft->align(TOP,true,false);
    topLeft->align(LEFT,true,false);

    src.x = BORDER_IMGWIDTH - BORDER_CORNERWIDTH;
    dest.x = bounds.x - BORDER_CORNERWIDTH;
    GUI::Element* topRight = uniqueElement(_tex,src,dest);
    topRight->align(TOP,true,false);
    topRight->align(RIGHT,true,false);

    src.y = BORDER_IMGWIDTH - BORDER_CORNERWIDTH;
    dest.y = bounds.y - BORDER_CORNERWIDTH;
    GUI::Element* bottomRight = uniqueElement(_tex,src,dest);
    bottomRight->align(BOTTOM,true,false);
    bottomRight->align(RIGHT,true,false);

    src.x = 0;
    dest.x = 0;
    GUI::Element* bottomLeft = uniqueElement(_tex,src,dest);
    bottomLeft->align(BOTTOM,true,false);

    //==================== Tags ====================

    std::cout<<"number of players: "<<_numPlayers<<"\n";

    src.h = BORDER_IMGWIDTH - BORDER_CORNERWIDTH - BORDER_CORNERWIDTH;
    src.w = src.h;
    src.x = BORDER_CORNERWIDTH;
    src.y = 0;

    dest = src;

    dest.x = (bounds.x / 2) - (src.w / 2);
    GUI::Element* top = uniqueElement(_tex,src,dest);
    top->centre(true,false);
    top->align(TOP,true,false);

    src.y = BORDER_IMGWIDTH - src.h;
    dest.y = bounds.y - src.h;
    GUI::Element* bottom = uniqueElement(_tex,src,dest);
    bottom->centre(true,false);
    bottom->align(BOTTOM,true,false);

    if (_numPlayers == 2)
    {
        return;
    }

    src.y = BORDER_CORNERWIDTH;
    dest.y = (bounds.y / 2) - (src.h / 2);  
    src.x = BORDER_IMGWIDTH - src.w;
    dest.x = bounds.x - src.w;
    GUI::Element* right = uniqueElement(_tex,src,dest);
    right->centre(true,false);
    right->align(RIGHT,true,false);

    if (_numPlayers == 3)
    {
        return;
    }

    src.x = 0;
    dest.x = 0;
    GUI::Element* left = uniqueElement(_tex,src,dest);
    left->centre(true,false);
    left->align(LEFT,true,false);
}

void GUI::DealerGUI::sendNameAway(const unsigned int &_playerID)
{
    GUI::Player* thatPlayer = &m_players[_playerID];
    thatPlayer->nameLabel->moveTo(thatPlayer->pos_offScreen);
}

void GUI::DealerGUI::bringNameBack(const unsigned int &_playerID)
{
    GUI::Player* thatPlayer = &m_players[_playerID];
    thatPlayer->nameLabel->align(thatPlayer->orient,true);
    SDL_Point newPos = thatPlayer->nameLabel->getPos();
    switch (thatPlayer->orient)
    {
        case BOTTOM : newPos.y -= 10; break;
        case TOP    : newPos.y += 10; break;
        case LEFT   : newPos.x += 10; break;
        case RIGHT  : newPos.x -= 10; break;
    }

    thatPlayer->nameLabel->moveTo(newPos);
}

void GUI::DealerGUI::splitPot(const std::vector<unsigned int> &_winnerIDs, const bool &_hasRemainder)
{
    for (std::vector<unsigned int>::const_iterator it = _winnerIDs.begin(); it != _winnerIDs.end(); ++it)
    {
        GUI::Player* thatPlayer = &m_players[(*it)];
        GUI::Element* theirChips = uniqueElement(m_pot);
        theirChips->setPos(m_potPos);
        theirChips->moveTo(thatPlayer->pos_offScreen);
        theirChips->kill();
    }

    if (!_hasRemainder)
    {
        SDL_Point goAway = {-128,-128};
        m_pot->setPos(goAway);
    }
}
