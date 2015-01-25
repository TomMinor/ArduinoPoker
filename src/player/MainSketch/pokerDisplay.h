/// @brief display class
/// @author Michelle Wu
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
    
    /// @brief displayCard
    /// @param [in] _rank, rank of the card
    /// @param [in] _suit, suit of the card
    /// @param [in] _x, x position on the lcd
    /// @param [in] _y, y position on the lcd
    /// @param [in] _nCard, number of the card out of the total
    /// @param [in] _totCards, total number of cards
    void displayCard( uint8_t _rank, uint8_t _suit, int _x, int _y, int _nCard, int _totCards );
    
    /// @brief displayName
    /// @param [in] _line, line to be displayed..
    /// @param [in] _name name to be displayed
    void displayName(char* _name);
    
    /// @brief displayMoney
    /// @param [in] _line, line to be displayed.
    /// @param [in] _money, money to be displayed.
    void displayMoney(uint8_t _line, uint16_t _money);
    
    ///@brief displayCards
    ///@param [in] _line, what line you want it printed on. 
    ///@param [in] _numCards, number of cards.
    ///@param [in] _cards{}, array of cards being passed to display.
    void displayCards(uint8_t _line, uint8_t _numCards, card _cards[]);

       
    /// @brief createCustomChar
    void createCustomChar();
    
    /// @brief displays "Waiting cards" on lcd
    void waitCards();
    
    ///@brief winner, prints a winning message.
    ///@param [in] money that the player has one.
    void winner(uint8_t _money);

    
    /// @brief resetScreen, prints the reset screen text.
    void screenReset();
        
    
    
private:
    
    /// @brief x position on the lcd screen
    int m_x;
    
    /// @brief y position on the lcd screen
    int m_y;
    
};

#endif
