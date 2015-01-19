//#include <player.h>
// include the library code:
#include <LiquidCrystal.h>

#include "player.h"

// couple things just for testing
#define PlaceBet       1
#define ReceiveCard    2
#define Reset          3
#define SetName        4
#define GetName        5

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

class input;



void setup() 
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
   
}

void loop() 
{
   //boolean dick;
   //input test(0);
   
   //uint8_t but;
   
   //dick = test.menuYesNo(1);  
  //static player test(500, 2);
  
  int command = getCommand();
  
  lcd.clear();
  lcd.print(String(command));
  
  delay(2000);
  
  //test.placeBet(200, 10);
  
//  lcd.clear();
//  //lcd.print(String(test.getMoney()));
//  
//  delay(5000);
}
