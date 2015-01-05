#ifndef DEALERGUI_H
#define DEALERGUI_H

#include "elementmaker.h"
#include "hand.h"
#include <vector>
#include <boost/shared_ptr.hpp>

typedef struct
{
    Uint8 id;
    SDL_Point pos_onScreen;
    SDL_Point pos_offScreen;
    std::string name;
    Orientation orient;
} Player;

class DealerGUI
{
public:
    DealerGUI(const unsigned int &_numPlayers, CardInfo* _cardInfo, LabelFormat *_labelFormat);
    void broadcastMessage(const std::string &_message);
    void setPlayerName(const unsigned int &_id, std::string _name);
    void dealCardTo(const unsigned int &_playerID, const CardType &_type);
    void receiveBetFrom(const unsigned int &_playerID, Uint16 _amount);
    void reset();
    void showWinner(std::vector<Player> _winners, std::vector<Hand> _winningHands);

    void update();
    void draw();

private:
    SDL_Renderer* m_renderer;
    //unsigned int m_numPlayers;
    ElementMaker m_maker;
    float m_messageTimeout;
    std::vector<Player> m_players;
    std::vector< boost::shared_ptr<Element> > m_elements;

    Player createPlayer(const Uint8 &_id, const std::string &_name, const Orientation &_orient, const int _offset);
    void removeFromElementVector(Element* _element);
};

#endif // DEALERGUI_H
