#ifndef POKERDISPLAY_H__
#define POKERDISPLAY_H__

#include "Arduino.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

class display
{
  public:
  
      display();
      ~display();
      void displayCard();
  
  private:
  
      int m_x;

};

#endif


