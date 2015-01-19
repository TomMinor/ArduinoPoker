#ifndef POKERDISPLAY_H__
#define POKERDISPLAY_H__

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <string.h>

extern LiquidCrystal lcd;

class display
{
  public:
  
    display(int _totCards);
    ~display();
    void displayCard( uint8_t _rank, uint8_t _suit, int _x, int _y, int _nCard );
    void createCustomChar();
  
  private:
  
    int m_x;
    int m_y;
    char m_rank[6];
    char m_suit[8];
    int m_totCards;
    int m_nCard;
};

#endif


