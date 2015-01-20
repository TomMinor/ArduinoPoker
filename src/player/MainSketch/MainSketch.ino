#include <LiquidCrystal.h>
#include "pokerDisplay.h"
#include "player.h"
#include "input.h"


LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


player test(80, 2);

void setup() 
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16,2);
}

void loop() 
{
  unsigned int bet; 
  bet = test.placeBet(100, 50);
  
  lcd.clear();
  
  lcd.print(String(bet));
  
  delay(2000);
  
}
