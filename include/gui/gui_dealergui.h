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

namespace GUI
{

typedef struct
{
    player* playerClass;
    SDL_Point pos_onScreen;
    SDL_Point pos_offScreen;
    Orientation orient;
    Label* nameLabel;
} Player;

class DealerGUI
{
public:
    DealerGUI();
    ~DealerGUI();

    Hand* m_publicCards;
    void initialise(std::vector<player*> _players, std::vector<PlayingCard> _publicCards);//init SDL and bring up the window etc.
    void broadcastMessage(const std::string &_message, const unsigned int &_duration = 128);
    void setPlayerName(const unsigned int &_playerID, std::string _name);
    void dealCardTo(const unsigned int &_playerID, const PlayingCard &_type);
    void receiveBetFrom(const unsigned int &_playerID, Uint16 &_amount, bool _isFirstBet = false);
    void addPublicCard(const PlayingCard &_type);
    //this returns a vector of hands; make sure to store it and burn each one before starting a new round
    std::vector<Hand*> showWinner(std::vector<player*> _winners);

    //use these functions to convert the other systems' classes/structs to the GUI system's
    //(probably no longer needed)
    CardType convert(const PlayingCard &_card);
    Player convert(const player &_player);
    Hand convert(const std::vector<PlayingCard> &_cards);

    SDL_Point getCentre();
    SDL_Point getScreenDimensions();

    //use these functions to store references to elements that you
    //want to control manually but draw/update/destroy automatically
    //avoid creating elements without using these, otherwise there is no guarantee the memory will be deallocated
    Card* uniqueCard(const PlayingCard &_type, const unsigned int &_playerID);
    Card* uniqueCard(const PlayingCard &_type, const Orientation &_orient = BOTTOM);
    Label* uniqueLabel(const std::string &_inputString, const unsigned int &_playerID, const int &_lifetime = 0);
    Label* uniqueLabel(const std::string &_inputString, const Orientation &_orient = BOTTOM, const int &_lifetime = 0);
    Hand* uniqueHand(const std::vector<PlayingCard> &_cards, const unsigned int &_playerID);
    Hand* uniqueHand(const std::vector<PlayingCard> &_cards, const Orientation &_orient = BOTTOM);
    Element* uniqueElement(SDL_Texture* _tex, const Orientation &_orient = BOTTOM);

    void update();
    void draw();
    void reset(std::vector<player*> _players = std::vector<player*>(), std::vector<PlayingCard> _publicCards = std::vector<PlayingCard>());

private:

    SDL_Renderer* m_renderer;
    SDL_Texture* m_renderTarget;
    GUI::ElementMaker m_maker;
    SDL_Point m_deckPos;
    SDL_Point m_potPos;
    Element* m_pot;
    std::vector< Player > m_players;
    std::vector< boost::shared_ptr<Element> > m_elements;
    std::vector< boost::shared_ptr<Hand> > m_hands;
    std::vector< Label* > m_activeMessages;

    Player createPlayer(player* _playerRef, const Orientation &_orient, const int _offset);
    void setUpUniqueElements(std::vector<PlayingCard> _publicCards);
    void setUpPlayers(std::vector<player*> _players);

    void SDLErrorExit(const std::string &_msg);
    void clearScreen(SDL_Renderer *_ren,char _r,char _g,char _b	);
};

}

#endif // DEALERGUI_H
