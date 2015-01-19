#include "pokerDisplay.h"
extern LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

display::display(int _totCards)
{
    m_totCards = _totCards;
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

void display::displayCard(uint8_t _rank, uint8_t _suit, int _x, int _y, int _nCard)
{
    //Suit
    m_x = _x;
    m_y = _y;
    m_nCard = _nCard;
    
    if (_suit == 1<<4 || _suit == 00010000){
        strcpy(m_suit,"DIAMOND");
        lcd.setCursor(m_x,m_y);
        lcd.write(byte(0));
    }
    else if(_suit == 1<<5 || _suit == 00100000){
        strcpy(m_suit,"HEART");
        lcd.setCursor(m_x,m_y);
        lcd.write(1);
    }
    else if(_suit == 1<<6 || _suit == 01000000){
        strcpy(m_suit,"CLUB");
        lcd.setCursor(m_x,m_y);
        lcd.write(2);
    }
    else if(_suit == 1<<7 || _suit == 10000000){
        strcpy(m_suit,"SPADE");
        lcd.setCursor(m_x,m_y);
        lcd.write(3);
    }
    else{
        lcd.clear();
        lcd.print("No valid suit.");
    }
    
    //Rank
    
    if (_rank == 0x01){
        strcpy(m_rank,"TWO");
        lcd.setCursor(m_x+1,m_y);
        lcd.print("2");
    }
    else if(_rank == 0x02) {
        strcpy(m_rank,"THREE");
        lcd.setCursor(m_x+1,m_y);
        lcd.print("3");
    }
    else if(_rank == 0x03){
        strcpy(m_rank,"FOUR");
        lcd.setCursor(m_x+1,m_y);
        lcd.print("4");
    }
    else if(_rank == 0x04){
        strcpy(m_rank,"FIVE");
        lcd.setCursor(m_x+1,m_y);
        lcd.print("5");
    }
    else if(_rank == 0x05){
        strcpy(m_rank,"SIX");
        lcd.setCursor(m_x+1,m_y);
        lcd.print("6");
    }
    else if(_rank == 0x06){
        strcpy(m_rank,"SEVEN");
        lcd.setCursor(m_x+1,m_y);
        lcd.print("7");
    }
    else if(_rank == 0x07){
        strcpy(m_rank,"EIGHT");
        lcd.setCursor(m_x+1,m_y);
        lcd.print("8");
    }
    else if(_rank == 0x08){
        strcpy(m_rank,"NINE");
        lcd.setCursor(m_x+1,m_y);
        lcd.print("9");
    }
    else if(_rank == 0x09){
        strcpy(m_rank,"TEN");
        lcd.setCursor(m_x+1,m_y);
        lcd.print("T");
    }
    else if(_rank == 0x0A){
        strcpy(m_rank,"JACK");
        lcd.setCursor(m_x+1,m_y);
        lcd.print("J");
    }
    else if(_rank == 0x0B){
        strcpy(m_rank,"QUEEN");
        lcd.setCursor(m_x+1,m_y);
        lcd.print("Q");
    }
    else if(_rank == 0x0C){
        strcpy(m_rank,"KING");
        lcd.setCursor(m_x+1,m_y);
        lcd.print("K");
    }
    else if(_rank == 0x0D){
        strcpy(m_rank,"ACE");
        lcd.setCursor(m_x+1,m_y);
        lcd.print("A");
    }
    else{
        lcd.clear();
        lcd.print("No valid rank.");
    }
    
    if(m_nCard != m_totCards)
    {
        lcd.setCursor(_x+2,0);
        lcd.print("|");
    }
    
}


