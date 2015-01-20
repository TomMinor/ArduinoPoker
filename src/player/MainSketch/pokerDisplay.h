#ifndef POKERDISPLAY_H__
#define POKERDISPLAY_H__

#include "Arduino.h"
#include <LiquidCrystal.h>

extern LiquidCrystal lcd;

class display
{
  public:
  
      display();
      ~display();
      void createCustomChar();
      void displayCard();
  
  private:
  
      int m_x;

};

#endif


