#include "include/gui_dealergui.h"
#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <sstream>

#define OFFSCREENOFFSET 36
#define COOLDOWNTIME 32

GUI_DealerGUI::GUI_DealerGUI(const unsigned int &_numPlayers, const GUI_CardInfo *_cardInfo, const GUI_LabelFormat *_labelFormat) :
    //m_publicCards(Hand(SDL_Point(),std::vector<Card>(),BOTTOM)),
    m_renderer(_cardInfo->ren),
    m_maker(GUI_ElementMaker(_cardInfo, _labelFormat))
{
    switch (_numPlayers)
    {
        case 2 :
            m_players.push_back(createPlayer(1,std::string("Player 1"),BOTTOM,8));
            m_players.push_back(createPlayer(2,std::string("Player 2"),TOP,8));
            break;
        case 3 :
            m_players.push_back(createPlayer(1,std::string("Player 1"),BOTTOM,8));
            m_players.push_back(createPlayer(2,std::string("Player 2"),RIGHT,8));
            m_players.push_back(createPlayer(3,std::string("Player 3"),TOP,8));
            break;
        case 4 :
            m_players.push_back(createPlayer(1,std::string("Player 1"),BOTTOM,8));
            m_players.push_back(createPlayer(2,std::string("Player 2"),RIGHT,8));
            m_players.push_back(createPlayer(3,std::string("Player 3"),TOP,8));
            m_players.push_back(createPlayer(4,std::string("Player 4"),LEFT,8));
            break;
        default :
            std::cout<<"Invalid player count!\n";
            m_players.push_back(createPlayer(1,std::string("You silly bish"),BOTTOM,64));
    }
}

GUI_DealerGUI::~GUI_DealerGUI()
{
    //deallocate memory
    m_elements.erase(m_elements.begin(),m_elements.end());
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

    SDL_Point point = {128,128};//fix this later
    newCard->setPos(point);
    newCard->moveTo(thatPlayer.pos_offScreen);
    newCard->kill();
}

void GUI_DealerGUI::receiveBetFrom(const unsigned int &_playerID, Uint16 &_amount)
{
    if (_playerID > m_players.size())
    {
        std::cerr<<"ID of non-existent player passed!\n";
        return;
    }
    GUI_Player thatPlayer = m_players[_playerID];

    std::cout<<"Receiving bet of £"<<_amount<<" from "<<thatPlayer.name<<"\n";

    std::stringstream amountStream;
    amountStream << _amount;
    std::string betString = std::string("$") + amountStream.str();

    boost::shared_ptr<GUI_Element> betLabel(m_maker.makeLabel(betString,thatPlayer.orient,32));
    m_elements.push_back(betLabel);

    SDL_Point point = {160,128};//fix this later
    betLabel->setPos(thatPlayer.pos_offScreen);
    betLabel->moveTo(point);
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
//    for (std::vector< boost::shared_ptr<Element> >::iterator it; it!=m_elements.end(); ++it)
//    {
//        (*it)->draw();
//    }

    for (int i=0; i<(int)m_elements.size(); ++i)
    {
            m_elements[i]->draw();
    }
}

GUI_Player GUI_DealerGUI::createPlayer(const Uint8 &_id, const std::string &_name, const GUI_Orientation &_orient, const int _offset)
{
    //onScreen is the position where this player's public items will be drawn
    //offScreen is where items will be moved to make it look like they are being given to this player
    //_offset is how far from this player's side of the screen the onScreen position will be
    int width, height;
    //SDL_GetRendererOutputSize(m_renderer, &width, &height);
    width=320;
    height=256;
    std::cout<<"Screen width: "<<width<<" Screen height: "<<height<<"\n";
    SDL_Point onScreen, offScreen;

    switch(_orient)
    {
        case BOTTOM :
            onScreen.x = width/2;
            offScreen.x = width/2;
            onScreen.y = height - _offset;
            offScreen.y = height + OFFSCREENOFFSET;
            break;

        case TOP :
            onScreen.x = width/2;
            offScreen.x = width/2;
            onScreen.y = _offset;
            offScreen.y = -OFFSCREENOFFSET;
            break;

        case RIGHT :
            onScreen.x = _offset;
            offScreen.x = -OFFSCREENOFFSET;
            onScreen.y = height/2;
            offScreen.y = height/2;
            break;

        case LEFT :
            onScreen.x = width - _offset;
            offScreen.x = width + OFFSCREENOFFSET;
            onScreen.y = height/2;
            offScreen.y = height/2;
            break;

        default :
            onScreen.x = width/2;
            onScreen.y = height/2;
            offScreen.x = width/2;
            offScreen.y = height/2;
    }

    std::cout<<_name<<"'s off-screen position at ("<<offScreen.x<<", "<<offScreen.y<<")\n";

    GUI_Player temp = {_id, onScreen, offScreen, _name, _orient};
    return temp;
}

SDL_Point GUI_DealerGUI::getCentre()//THIS IS BROKEN :c
{
    SDL_Point centre;
    int width, height;
    SDL_RenderGetLogicalSize(m_renderer,&width,&height);
    centre.x = width / 2;
    centre.y = height / 2;
    return centre;
}

GUI_Card* GUI_DealerGUI::uniqueCard(const GUI_CardType &_type, const GUI_Orientation &_orient)
{
    boost::shared_ptr<GUI_Card> temp(m_maker.makeCard(_type,_orient));
    m_elements.push_back(temp);
    return temp.get();
}

GUI_Label* GUI_DealerGUI::uniqueLabel(const std::string &_inputString, const GUI_Orientation &_orient, const int &_lifetime)
{
    boost::shared_ptr<GUI_Label> temp(m_maker.makeLabel(_inputString,_orient,_lifetime));
    m_elements.push_back(temp);
    return temp.get();
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
