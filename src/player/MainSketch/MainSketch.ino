#include <LiquidCrystal.h>
#include "pokerDisplay.h"
#include "player.h"
#include "input.h"


LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


void setup() 
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16,2);
}

void loop() 
{
   
  lcd.print("butt");
}
