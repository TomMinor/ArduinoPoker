/// @brief player class
/// @author George Madges, Michelle Wu
/// @version 1.0
/// @date 21/01/2015

#ifndef PLAYER_H__
#define PLAYER_H__

#include "input.h"
#include "comms.h"
#include "pokerDisplay.h"
#include <LiquidCrystal.h>
#include <Arduino.h>

struct card
{
  uint8_t suit;
  uint8_t rank; 
};

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
    
    /// @brief Eddy's variables
    //eddy variables
    char character;
    uint16_t uInteger;
    
    
        ///@brief checkHeader, a function send header info of an outgoing packet.
    ///@brief The serial, header contains :[dataType][total bytes]
    ///@param [in] _data type  : defined by the header enum, the type of data, eg card,betstate,.... 
    void sendHeader(uint8_t _datatype) ;
    bool RecieveConfirmation();

  public:

    /// @brief ctor.
    player();

    /// @brief dtor
    ~player();

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
    void resetPlayer(uint16_t _money, uint16_t _cardNum);

    /// @brief resetCards
    /// @brief reset only the cards. leave everything else.
    void resetCards();

    /// @brief getMoney
    /// @param [out] returns value of players money.
    uint16_t getMoney() { return m_money; }

    /// @brief getName
    /// @param [out] returns name of player.
    char* getName() { return m_playerName; }
    
    
    /// @brief showPlayerData().
    /// @brief Method prints the players data on the screen.
    void showPlayerData();
    
       
    //Eddy's stuff
  ///@Comms funtion declerations
    ///@brief sendData , A set of overloaded functions to handle different data types , bool, uint8_t, uin16_t and char arrays
    ///@param [in] _data       : The data to send
    ///@param [in] _data type  : defined by the header enum, the type of data, eg card,betstate,.... 
    bool sendBet (uint16_t _data,     uint8_t _datatype);
    bool sendName(char     _data[15], uint8_t _datatype);
    bool sendFold(bool     _data,     uint8_t _datatype);


};

#endif
