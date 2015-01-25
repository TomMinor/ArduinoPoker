/// @brief player class
/// @author George Madges, Michelle Wu
/// @version 1.0
/// @date 21/01/2015

#ifndef PLAYER_H__
#define PLAYER_H__

#include "input.h"
#include "card.h"
#include "comms.h"
#include "pokerDisplay.h"
#include "Arduino.h"
#include <LiquidCrystal.h>


class player
{
  private:

    /// @brief The players money
    uint16_t m_money;

    /// @brief Number of cards being held by the player.
    uint8_t m_numCards;

    /// @brief Array of chars storing the players name.
    char m_playerName[15];

    /// @brief Array of cards.
    card m_cards[5];
    
    /// @brief Display
    display m_display;
    
    /// @brief input class variable.
    input m_button;   

  public:

    /// @brief ctor.
    player();

    /// @brief dtor
    ~player();
    
    /// @brief setMoney
    /// @param [in] _money, set the money.
    void setMoney(uint16_t _money);

    /// @brief placeBet
    /// @param [in] _max, maximum bet limit.
    /// @param [in] _min, minimum bet limit.
    /// @param [out] amount of bet being placed.
    uint16_t placeBet(uint16_t _max, uint16_t _min);

    /// @brief receiveMoney
    /// @param [in] _money, amount of money being given to the player.
    void receiveMoney(uint16_t _money);

    /// @brief recieveCard
    /// @brief Recieve card from dealer and add to the players own card array.
    /// @param [in] _cards[], array of cards sent by comms.
    void receiveCard(uint8_t _block, uint8_t _cards[] );

    /// @brief setName
    /// @brief asks the player to set their name.
    void setName();

    /// @brief resetPlayer
    /// @param _money, amount of money the player starts with.
    /// @param _cardNum, amount of cards the player will be given.
    void resetPlayer(uint16_t _money);

    /// @brief resetCards
    /// @brief reset only the cards. leave everything else.
    void resetCards();

    /// @brief getMoney
    /// @param [out] returns value of players money.
    uint16_t getMoney() { return m_money; }

    /// @brief getName
    /// @param [out] returns name of player.
    char* getName() { return m_playerName; }
    
    /// @brief checkFirstcard
    /// @param [out] returns bool if first card is empty.
    bool checkFirstCard();
        
    /// @brief joinGame
    /// @brief Method task the player to join, stops them from carrying on unless they do.
    /// @brief infinite loop if they so no.
    void joinGame();
       
    void playerDataScreen();
    
<<<<<<< HEAD
=======
    /// @brief PlayerDataScreen().
    /// @brief Method prints the players data on the screen.
    void playerDataScreen();
    
>>>>>>> origin/master
};

#endif
