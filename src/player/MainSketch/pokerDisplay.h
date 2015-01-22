/// @brief display class
/// @author Michelle Wu
/// @version 1.0
/// @date 22/01/2015

#ifndef POKERDISPLAY_H__
#define POKERDISPLAY_H__

#include "Arduino.h"
#include <LiquidCrystal.h>
#include "card.h"

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
    
    /// @brief createCustomChar
    void createCustomChar();
    
    /// @brief displays "Waiting cards" on lcd
    void waitCards();
    
private:
    
    /// @brief x position on the lcd screen
    int m_x;
    
    /// @brief y position on the lcd screen
    int m_y;
    
};

#endif
