#ifndef DEALERGUI_H
#define DEALERGUI_H

#include "elementmaker.h"
#include "hand.h"
#include "task.h"
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
    DealerGUI(const unsigned int &_numPlayers, const CardInfo* _cardInfo, const LabelFormat *_labelFormat);
    ~DealerGUI();
    void broadcastMessage(const std::string &_message, const unsigned int &_duration = 128);
    void setPlayerName(const unsigned int &_id, std::string _name);
    void dealCardTo(const unsigned int &_playerID, const CardType &_type);
    void receiveBetFrom(const unsigned int &_playerID, Uint16 &_amount);
    void reset();
    void showWinner(std::vector<Player> _winners, std::vector<Hand> _winningHands);

    //use these functions to store references to cards/labels that you can control manually
    //but will be drawn/updated/destroyed automatically
    Card* uniqueCard(const CardType &_type, const Orientation &_orient);
    Label* uniqueLabel(const std::string &_inputString, const Orientation &_orient, const int &_lifetime = 0);
    Hand uniqueHand(const std::vector<CardType> &_cards, const Orientation &_orient);

    void update();
    void draw();

private:
    SDL_Texture* m_debugDotTexture;

    SDL_Renderer* m_renderer;
    //unsigned int m_numPlayers;
    ElementMaker m_maker;
    std::vector<Player> m_players;
    std::vector< boost::shared_ptr<Element> > m_elements;
    //we may receive multiple function inputs simultaneously which will result in strange visuals;
    //this queue system is implemented to execute visual tasks one after the other with a short pause in between for a more natural feel
    //std::vector< boost::shared_ptr<Task> > m_taskQueue;

    Player createPlayer(const Uint8 &_id, const std::string &_name, const Orientation &_orient, const int _offset);

    void removeFromElementVector(Element* _element);
    SDL_Point getCentre();
};

#endif // DEALERGUI_H
