#ifndef DEALERGUI_H
#define DEALERGUI_H

<<<<<<< HEAD
#include "elementmaker.h"
#include "hand.h"
#include <vector>

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
    unsigned int m_numPlayers;
    ElementMaker m_maker;
    //Hand* m_publicCards;
    float m_messageTimeout;
    //Card m_deck;
    //Element m_pot;
=======
class DealerGUI
{
public:
    DealerGUI();

private:
    unsigned int m_numPlayers;

>>>>>>> 9a857e697db5c34734e45771dbf4daa043b18f26
};

#endif // DEALERGUI_H
