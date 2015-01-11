#ifndef DEALERGUI_H
#define DEALERGUI_H

#include "gui_elementmaker.h"
#include "gui_hand.h"
#include <vector>
#include <boost/shared_ptr.hpp>

typedef struct
{
    Uint8 id;
    SDL_Point pos_onScreen;
    SDL_Point pos_offScreen;
    std::string name;
    GUI_Orientation orient;
} GUI_Player;

class GUI_DealerGUI
{
public:
    GUI_DealerGUI(const unsigned int &_numPlayers, const GUI_CardInfo* _cardInfo, const GUI_LabelFormat *_labelFormat);
    ~GUI_DealerGUI();
    void broadcastMessage(const std::string &_message, const unsigned int &_duration = 128);
    void setPlayerName(const unsigned int &_id, std::string _name);
    void dealCardTo(const unsigned int &_playerID, const GUI_CardType &_type);
    void receiveBetFrom(const unsigned int &_playerID, Uint16 &_amount);
    void reset();
    void showWinner(std::vector<GUI_Player> _winners, std::vector<GUI_Hand> _winningHands);

    //use these functions to store references to cards/labels that you can control manually
    //but will be drawn/updated/destroyed automatically
    GUI_Card* uniqueCard(const GUI_CardType &_type, const GUI_Orientation &_orient);
    GUI_Label* uniqueLabel(const std::string &_inputString, const GUI_Orientation &_orient, const int &_lifetime = 0);
    GUI_Hand uniqueHand(const std::vector<GUI_CardType> &_cards, const GUI_Orientation &_orient);

    void update();
    void draw();

private:
    SDL_Texture* m_debugDotTexture;

    SDL_Renderer* m_renderer;
    //unsigned int m_numPlayers;
    GUI_ElementMaker m_maker;
    std::vector<GUI_Player> m_players;
    std::vector< boost::shared_ptr<GUI_Element> > m_elements;
    //we may receive multiple function inputs simultaneously which will result in strange visuals;
    //this queue system is implemented to execute visual tasks one after the other with a short pause in between for a more natural feel
    //std::vector< boost::shared_ptr<Task> > m_taskQueue;

    GUI_Player createPlayer(const Uint8 &_id, const std::string &_name, const GUI_Orientation &_orient, const int _offset);

    void removeFromElementVector(GUI_Element* _element);
    SDL_Point getCentre();
};

#endif // DEALERGUI_H
