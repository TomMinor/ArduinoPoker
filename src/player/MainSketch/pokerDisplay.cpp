#include "pokerDisplay.h"

display::display()
{

}

display::~display()
{

}


void display::createCustomChar()
{
    //Custom characters created using http://omerk.github.io/lcdchargen/
    
    byte diamond[8] = {
        0b00000,
        0b00100,
        0b01110,
        0b11101,
        0b11101,
        0b01110,
        0b00100,
        0b00000
    };
    
    byte heart[8] = {
        0b00000,
        0b01010,
        0b11111,
        0b11111,
        0b11111,
        0b01110,
        0b00100,
        0b00000
    };
    
    byte club[8] = {
        0b01010,
        0b00100,
        0b10101,
        0b11111,
        0b10101,
        0b00100,
        0b01110,
        0b00000
    };
    
    byte spade[8] = {
        0b00000,
        0b00100,
        0b01110,
        0b11111,
        0b11111,
        0b01110,
        0b10101,
        0b00000
    };
    
    lcd.createChar(0, diamond);
    lcd.createChar(1, heart);
    lcd.createChar(2, club);
    lcd.createChar(3, spade);
    
}


void display::displayCard()
{

}

