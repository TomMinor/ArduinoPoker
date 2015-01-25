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
    /// \brief A pointer to the dealer-side player object.
    const player * playerClass;

    /// \brief An SDL point representing where the player will place their public virtual items e.g. cards.
    SDL_Point pos_onScreen;

    /// \brief An SDL point outside the screen boundaries representing where items will be sent/appear from to look like they belong to the player sitting there.
    SDL_Point pos_offScreen;

    /// \brief The edge of the screen this player will be sitting at.
    Orientation orient;

    /// \brief A pointer to a label object displaying the player's name which will be drawn on their side of the screen.
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
    void initialise(std::vector<const player*> _players,
                    const std::vector<PlayingCard>& _publicCards,
                    const unsigned int &_windowWidth = 480,
                    const unsigned int &_windowHeight = 360,
                    const unsigned int &_pixelScale = 3);//init SDL and bring up the window etc.

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
    void dealCardTo(const unsigned int &_playerID, const PlayingCard &_type);

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

    /// \brief Pushes the specified player's name off-screen to signify that they are not currently in play.
    /// \param _playerID The index into the m_players vector to find the player whose name to send away.
    void sendNameAway(const unsigned int &_playerID);

    /// \brief Puts the specified player's name back on-screen.
    /// \param _playerID The index into the m_players vector to find the player whose name to bring back.
    void bringNameBack(const unsigned int &_playerID);

    /// \brief Does a visual representation of sending the chips in the pot to the winning player(s).
    /// \param _winnerIDs A vector containing the index(es) of the winning player(s).
    /// \param _hasRemainder True if the pot cannot be split evenly between the winning players, thus leaving some chips still in it.
    void splitPot(const std::vector<unsigned int> &_winnerIDs, const bool &_hasRemainder);

    /// \brief Broadcasts a message saying who has won this round and shows the cards they had in the middle of the screen. Can handle multiple winning players.
    /// \param _winners A vector of pointers to the winning players.
    /// \return A vector of pointers to the hands displayed on-screen. If the dealer (not the dealer GUI) wishes to start a new round without calling the reset() function,
    /// it is their responsibility to store these pointers and delete or burn the hands when the players are ready to begin a new round.
    std::vector<Hand*> showWinner(const std::vector<unsigned int> &_winnerIDs, const bool &_hasRemainder, const unsigned int &_winnings);

    //use these functions to convert the other systems' classes/structs to the GUI system's
    //(probably no longer needed)
    //CardType convert(const PlayingCard &_card);
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

    /// \brief Returns the specified player's on-screen position.
    inline SDL_Point getOnScreenPos(const unsigned int &_playerID) {return m_players[_playerID].pos_onScreen;}

    /// \brief Returns the specified player's off-screen position.
    inline SDL_Point getOffScreenPos(const unsigned int &_playerID) {return m_players[_playerID].pos_offScreen;}

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
    Element* uniqueElement(Element* _inputElement);

    /// \brief Calls the update() function of all the visual elements to keep their states moving.
    void update();

    /// \brief Draws all the elements in the window. Should probably always be called right after update() unless you're doing something fancy with different update and draw
    /// frequencies.
    void draw();

    /// \brief Resets the visual game state. DON'T USE THIS, IT'S BUGGY RIGHT NOW
    /// \param _players A vector of players to start the new game with. Pass no parameter to use the same players as the last game.
    /// \param _publicCards A vector of cards to start the river with in the new game.
    void reset(std::vector<const player *> _players = std::vector<const player*>(), std::vector<PlayingCard> _publicCards = std::vector<PlayingCard>());

private:

    /// \brief A pointer to the SDL rendering context.
    SDL_Renderer* m_renderer;

    /// \brief A pointer to an SDL texture containing the contents of the renderer. This is then upscaled by nearest-neighbour in the window for those lovely big pixels.
    SDL_Texture* m_renderTarget;

    /// \brief An element factory that effectively implements specialised constructors for element subclasses, making their creation much easier.
    GUI::ElementMaker m_maker;

    /// \brief The position of the deck of cards. Useful for the "spawn point" of a card being dealt to a player, for example.
    SDL_Point m_deckPos;

    /// \brief The position of the pot. Visual representations of a bet are sent to this location.
    SDL_Point m_potPos;

    /// \brief A pointer to the visual representation of the pot.
    Element* m_pot;

    /// \brief A vector containing a number of GUI player structs. Each one contains a pointer to a dealer-side player object as well as some extra info the GUI needs.
    std::vector< Player > m_players;

    /// \brief A vector containing smart pointers to all the active elements. Since each one is dynamically allocated, the smart pointers will deallocate their memory when
    /// they are cleared from the vector.
    std::vector< boost::shared_ptr<Element> > m_elements;

    /// \brief A vector containing smart pointers to all the active hands. Since each one is dynamically allocated, the smart pointers will deallocate their memory when
    /// they are cleared from the vector.
    std::vector< boost::shared_ptr<Hand> > m_hands;

    /// \brief A vector containing pointers to all the messages currently being displayed. This is so we can remove them when a new message is displayed and prevent text
    /// being drawn on top of other text and looking messy.
    std::vector< Label* > m_activeMessages;

    /// \brief Returns a GUI player struct with the given parameters.
    /// \param _playerRef A pointer to the dealer-side player object.
    /// \param _orient Which side of the screen-table this player should be sitting at.
    /// \param _offset How far from their side of the screen this player will place their virtual items e.g. cards.
    /// \return A GUI player struct.
    Player createPlayer(const player *_playerRef, const Orientation &_orient, const int _offset);

    /// \brief Creates most of the initial elements (e.g. deck, pot) and places them at their correct positions.
    /// \param _publicCards A vector containing the initial set of community cards. Can be empty if the dealer wishes to set this up later.
    /// \param _numPlayers The number of players; used by setUpBorder().
    void setUpUniqueElements(std::vector<PlayingCard> _publicCards = std::vector<PlayingCard>(), const unsigned int &_numPlayers = 4);

    /// \brief Creates and positions our pretty border. This has its own function because the border is resolution-independent and therefore made up of a number of different
    /// elements at specific positions, so a lot of lines of code are needed.
    /// \param _tex A pointer to the SDL texture to use.
    /// \param _numPlayers The number of "tags" (fancy boxes for player names) to create. Pass no argument here if the look of empty tags rather than empty sections of border
    /// is preferred.
    void setUpBorder(SDL_Texture* _tex, const unsigned int &_numPlayers = 4);

    /// \brief Creates all the GUI player structs to put into m_players and sets up their name labels in the correct positions.
    /// \param _players A vector containing pointers to all the dealer-side player objects.
    void setUpPlayers(std::vector<const player*> _players);

    /// \brief A convenient function to quit SDL and print a message if an error is encountered.
    /// \param _msg The error message to print to cerr.
    void SDLErrorExit(const std::string &_msg);

    /// \brief Turns the whole window one colour. Used just before drawing all the elements to prevent trails behind moving elements.
    /// \param _r The R value of the colour to use.
    /// \param _g The G value of the colour to use.
    /// \param _b The B value of the colour to use.
    void clearScreen(Uint8 _r,Uint8 _g,Uint8 _b);
};

}

#endif // DEALERGUI_H
