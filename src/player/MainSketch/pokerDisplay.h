/// @brief display class
/// @author Michelle Wu, George Madges
/// @version 1.0
/// @date 22/01/2015

#ifndef POKERDISPLAY_H__
#define POKERDISPLAY_H__

#include "card.h"
#include "Arduino.h"
#include <LiquidCrystal.h>

extern LiquidCrystal lcd;

class display
{
public:
    
    /// @brief ctor
    display();
    
    /// @brief dtor
    ~display();
    
    /// @brief createCustomChar
    void createCustomChar();

    /// @brief displayName
    /// @param [in] _name name to be displayed
    void displayName( char* _name );
    
    /// @brief displayMoney
    /// @param [in] _line, line to be displayed.
    /// @param [in] _money, money to be displayed.
    void displayMoney( uint8_t _line, uint16_t _money );
    
    /// @brief displayCard
    /// @param [in] _rank, rank of the card
    /// @param [in] _suit, suit of the card
    /// @param [in] _x, x position on the lcd
    /// @param [in] _y, y position on the lcd
    /// @param [in] _nCard, number of the card out of the total
    /// @param [in] _totCards, total number of cards
    void displayCard( uint8_t _rank, uint8_t _suit, int _x, int _y, int _nCard, int _totCards );
    
    /// @brief checkForCard
    /// @param [in] _card, card in the array you want to check.
    /// @param [out] returns bool if card is empty.
    bool checkForCard(card _card);   
    
    /// @brief displayCards
    /// @param [in] _line, what line you want it printed on. 
    /// @param [in] _numCards, number of cards.
    /// @param [in] _cards[], array of cards being passed to display.

    void displayCards(uint8_t _line, uint8_t _numCards, card _cards[]);
    
    /// @brief winner, prints a winning message.
    /// @param [in] money that the player has won.
    void winner(uint16_t _money);

    /// @brief resetScreen, prints the reset screen text.
    void screenReset();

};

#endif
