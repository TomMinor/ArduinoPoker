#include "include/dealergui.h"

#define OFFSCREENOFFSET 16

DealerGUI::DealerGUI(const unsigned int &_numPlayers, CardInfo *_cardInfo, LabelFormat *_labelFormat) :
    //m_publicCards(Hand(SDL_Point(),std::vector<Card>(),BOTTOM)),
    m_maker(ElementMaker(_cardInfo, _labelFormat))
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
            m_players.push_back(createPlayer(std::string("You silly bish"),BOTTOM,64));
    }
}

void DealerGUI::broadcastMessage(const std::string &_message)
{
}

void DealerGUI::update()
{
    for (std::vector< boost::shared_ptr<Element> >::iterator it; it!=m_elements.end(); ++it)
    {
        if((*it)->shouldKill())
        {
            m_elements.erase(it,it);//delete the element; the use of shared_ptr should ensure the memory is cleared up
        }
        else
        {
            (*it)->update();
        }
    }
}

void DealerGUI::draw()
{
    for (std::vector< boost::shared_ptr<Element> >::iterator it; it!=m_elements.end(); ++it)
    {
        (*it)->draw();
    }
}

Player DealerGUI::createPlayer(const std::string &_name, const Orientation &_orient, const int _offset)
{
    //onScreen is the position where this player's public items will be drawn
    //offScreen is where items will be moved to make it look like they are being given to this player
    //_offset is how far from this player's side of the screen the onScreen position will be
    int width, height;
    SDL_GetRendererOutputSize(m_renderer, &width, &height);
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

        case LEFT :
            onScreen.x = _offset;
            offScreen.x = -OFFSCREENOFFSET;
            onScreen.y = height/2;
            offScreen.y = height/2;
            break;

        case RIGHT :
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

    Player temp = {onScreen, offScreen, _name, _orient};
    return temp;
}
