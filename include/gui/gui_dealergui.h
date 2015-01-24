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

/// \brief Since the GUI requires a little more information about a given player than is contained in the player class, this struct contains that information as well
/// as a pointer to the original class.
typedef struct
{
    player* playerClass;
    SDL_Point pos_onScreen;
    SDL_Point pos_offScreen;
    Orientation orient;
    Label* nameLabel;
} Player;

/// \brief The main class used for displaying things on the screen.
///
/// The GUI class includes functions to be called for most of the events that will happen in the game such as dealing a card to a player, receiving a bet from a player or
/// adding a card to the public set. A unique example is the "showWinner()" function which returns a std::vector of Hands which must be burned outside of the GUI class
/// before a new round is started.
/// There are also functions to return dynamically allocated instances of visual elements (e.g. cards, text) that will be drawn, updated, and destroyed by the GUI class but
/// can be controlled externally.
/// Finally, there are the update() and draw() functions which should be called about 30 times a second during gameplay and the reset() function which should be used when
/// a new round is started.
class DealerGUI
{
public:
    DealerGUI();
    ~DealerGUI();

    /// \brief The "river" of cards on the table.
    Hand* m_publicCards;

    /// \brief Sets up SDL and all the initial elements and variables.
    /// \param _players A vector of all the players that will be taking part in the game.
    /// \param _publicCards A vector of the initial cards in the river. Can be empty and the cards added later with addPublicCard().
    void initialise(std::vector<player*> _players, std::vector<PlayingCard> _publicCards);//init SDL and bring up the window etc.

    /// \brief Prints a message that players on all sides of the table can read.
    /// \param _message The message to print.
    /// \param _duration How many update() calls this message will last for. Passing 0 will cause it to last forever (probably not a good idea).
    void broadcastMessage(const std::string &_message, const unsigned int &_duration = 128);

    /// \brief Changes a player's name.
    /// \param _playerID The index into the m_players vector to find the player whose name to set.
    /// \param _name The new name for the player.
    void setPlayerName(const unsigned int &_playerID, std::string _name);

    /// \brief Creates a card at the deck position and sends it off screen in the specified player's direction.
    /// \param _playerID The index into the m_players vector to find the player to send the card to.
    /// \param _type The type (rank and suit) of the card to send - usually irrelevant since the card will be face-down anyway.
    void dealCardTo(const unsigned int &_playerID, const PlayingCard &_type = PlayingCard(Rank::ACE,Suit::SPADE));

    /// \brief Sends a label denoting the amount the player is betting from their off-screen position to the pot, as well as printing a message saying how much this player
    /// is betting.
    /// \param _playerID The index into the m_players vector to find the player who we receive the bet from.
    /// \param _amount The amount in dollars to be displayed on the bet label.
    /// \param _isFirstBet True to set the message as "<Player> makes a bet of <Amount>", false to set the message as "<Player> raises the bet to <Amount>".
    void receiveBetFrom(const unsigned int &_playerID, Uint16 &_amount, bool _isFirstBet = false);

    /// \brief Moves a player's name label off-screen along with another label from the pot denoting the amount of money they take back out of it. A message is also sent
    /// saying that this player has been kicked from the round.
    /// \param _playerID The index into the m_players vector to find the player to kick.
    /// \param _money The amount of money in dollars that the player takes back out of the pot.
    void kickPlayer(const unsigned int &_playerID, const unsigned int &_money);

    /// \brief Puts the specified player's name label back in its usual position and sends a message saying that this player is back in the game.
    /// \param _playerID The index into the m_players vector to find the player to bring back.
    void addPlayerBack(const unsigned int &_playerID);

    /// \brief Creates a new card at the deck position and adds it to the river, face-up.
    /// \param _type The type of card (rank and suit) to add.
    void addPublicCard(const PlayingCard &_type);

    /// \brief Broadcasts a message saying who has won this round and shows the cards they had in the middle of the screen. Can handle multiple winning players.
    /// \param _winners A vector of pointers to the winning players.
    /// \return A vector of pointers to the hands displayed on-screen. If the dealer (not the dealer GUI) wishes to start a new round without calling the reset() function,
    /// it is their responsibility to store these pointers and delete or burn the hands when the players are ready to begin a new round.
    std::vector<Hand*> showWinner(std::vector<player*> _winners);

    //use these functions to convert the other systems' classes/structs to the GUI system's
    //(probably no longer needed)
    CardType convert(const PlayingCard &_card);
    Player convert(const player &_player);
    Hand convert(const std::vector<PlayingCard> &_cards);

    /// \brief Returns an SDL point in the centre of the window.
    SDL_Point getCentre();

    /// \brief Returns the point on the screen with the maximum possible co-ordinates. Useful for getting window dimensions.
    SDL_Point getScreenDimensions();

    /// \brief Returns the position of the deck. Useful when dealing with cards that are meant to look like they came from the deck.
    inline SDL_Point getDeckPos() {return m_deckPos;}

    /// \brief Returns the position of the pot. Useful for dealing with bets etc.
    inline SDL_Point getPotPos() {return m_potPos;}

    //use these functions to store references to elements that you
    //want to control manually but draw/update/destroy automatically
    //avoid creating elements outside of the GUI class without using these, otherwise there is no guarantee the memory will be deallocated

    /// \brief Returns a pointer to a card that will be drawn/updated/destroyed automatically.
    Card* uniqueCard(const PlayingCard &_type, const unsigned int &_playerID);
    /// \brief Returns a pointer to a card that will be drawn/updated/destroyed automatically.
    Card* uniqueCard(const PlayingCard &_type, const Orientation &_orient = BOTTOM);

    /// \brief Returns a pointer to a label that will be drawn/updated/destroyed automatically.
    Label* uniqueLabel(const std::string &_inputString, const unsigned int &_playerID, const int &_lifetime = 0);
    /// \brief Returns a pointer to a label that will be drawn/updated/destroyed automatically.
    Label* uniqueLabel(const std::string &_inputString, const Orientation &_orient = BOTTOM, const int &_lifetime = 0);

    /// \brief Returns a pointer to a hand that will be drawn/updated/destroyed automatically.
    Hand* uniqueHand(const std::vector<PlayingCard> &_cards, const unsigned int &_playerID);
    /// \brief Returns a pointer to a hand that will be drawn/updated/destroyed automatically.
    Hand* uniqueHand(const std::vector<PlayingCard> &_cards, const Orientation &_orient = BOTTOM);

    /// \brief Returns a pointer to an element that will be drawn/updated/destroyed automatically.
    Element* uniqueElement(SDL_Texture* _tex, const Orientation &_orient = BOTTOM);
    /// \brief Returns a pointer to an element that will be drawn/updated/destroyed automatically.
    Element* uniqueElement(SDL_Texture* _tex, const SDL_Rect &_srcRect, const SDL_Rect &_destRect, const Orientation &_orient = BOTTOM);

    /// \brief Calls the update() function of all the visual elements to keep their states moving.
    void update();

    /// \brief Draws all the elements in the window. Should probably always be called right after update() unless you're doing something fancy.
    void draw();

    /// \brief Resets the visual game state.
    /// \param _players A vector of players to start the new game with. Pass no parameter to use the same players as the last game.
    /// \param _publicCards A vector of cards to start the river with in the new game.
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
    void setUpBorder(SDL_Texture* _tex);
    void setUpPlayers(std::vector<player*> _players);

    void SDLErrorExit(const std::string &_msg);
    void clearScreen(SDL_Renderer *_ren,char _r,char _g,char _b	);
};

}

#endif // DEALERGUI_H
