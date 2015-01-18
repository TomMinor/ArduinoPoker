#include <LiquidCrystal.h>
#include "pokerDisplay.h"
#include "player.h"
#include "input.h"
player p(100,2);

void setup() 
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16,2);
  
}

void loop() 
{
   
  //lcd.print("butt");
  p.setName();
}
