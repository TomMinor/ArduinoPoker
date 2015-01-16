#ifndef DEALERGUI_H
#define DEALERGUI_H

#include "gui_elementmaker.h"
#include "gui_hand.h"

#include "include/dealer/playingcard.h"
#include "include/dealer/deck.h"
#include "include/dealer/player.h"
#include "include/dealer/pokerHands.h"

#include <vector>
#include <boost/shared_ptr.hpp>

typedef struct
{
    player* playerClass;
    SDL_Point pos_onScreen;
    SDL_Point pos_offScreen;
    GUI_Orientation orient;
    GUI_Label* nameLabel;
} GUI_Player;

class GUI_DealerGUI
{
public:
    GUI_DealerGUI();
    ~GUI_DealerGUI();
    void initialise(std::vector<player*> _players);//init SDL and bring up the window etc.
    void broadcastMessage(const std::string &_message, const unsigned int &_duration = 128);
    //void setPlayerName(const unsigned int &_playerID, std::string _name);
    void dealCardTo(const unsigned int &_playerID, const PlayingCard &_type);
    void receiveBetFrom(const unsigned int &_playerID, Uint16 &_amount, bool _isFirstBet = false);
    //this returns a vector of hands; make sure to store it and burn each one before starting a new round
    std::vector<GUI_Hand*> showWinner(std::vector<player*> _winners);

    //use these functions to convert the other systems' classes/structs to the GUI system's
    //(probably no longer needed)
    GUI_CardType convert(const PlayingCard &_card);
    GUI_Player convert(const player &_player);
    GUI_Hand convert(const std::vector<PlayingCard> &_cards);

    SDL_Point getCentre();
    SDL_Point getScreenDimensions();

    //use these functions to store references to elements that you
    //want to control manually but draw/update/destroy automatically
    //avoid creating elements without using these, otherwise there is no guarantee the memory will be deallocated
    GUI_Card* uniqueCard(const PlayingCard &_type, const unsigned int &_playerID);
    GUI_Card* uniqueCard(const PlayingCard &_type, const GUI_Orientation &_orient = BOTTOM);
    GUI_Label* uniqueLabel(const std::string &_inputString, const unsigned int &_playerID, const int &_lifetime = 0);
    GUI_Label* uniqueLabel(const std::string &_inputString, const GUI_Orientation &_orient = BOTTOM, const int &_lifetime = 0);
    GUI_Hand* uniqueHand(const std::vector<PlayingCard> &_cards, const unsigned int &_playerID);
    GUI_Hand* uniqueHand(const std::vector<PlayingCard> &_cards, const GUI_Orientation &_orient = BOTTOM);

    void update();
    void draw();
    void reset();

private:

    SDL_Renderer* m_renderer;
    SDL_Texture* m_renderTarget;
    GUI_ElementMaker m_maker;
    SDL_Point m_deckPos;
    SDL_Point m_potPos;
    std::vector< GUI_Player > m_players;
    std::vector< boost::shared_ptr<GUI_Element> > m_elements;
    std::vector< boost::shared_ptr<GUI_Hand> > m_hands;
    //we may receive multiple function inputs simultaneously which will result in strange visuals;
    //this queue system is implemented to execute visual tasks one after the other with a short pause in between for a more natural feel
    //std::vector< boost::shared_ptr<Task> > m_taskQueue;

    GUI_Player createPlayer(player* _playerRef, const GUI_Orientation &_orient, const int _offset);

    void SDLErrorExit(const std::string &_msg);
    void clearScreen(SDL_Renderer *_ren,char _r,char _g,char _b	);
};

#endif // DEALERGUI_H
