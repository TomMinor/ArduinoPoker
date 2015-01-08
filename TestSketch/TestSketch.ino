// include the library code:
#include <LiquidCrystal.h>

// couple things just for testing
#define PlaceBet       1
#define ReceiveCard    2
#define Reset          3
#define SetName        4
#define GetName        5

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() 
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  player test(100, 2);
  
  
}

void loop() 
{
  player test(100, 2);
  
  lcd.clear();
  lcd.print(String(test.getMoney()));
  
  delay(2000);
  
  test.placeBet(200, 10);
  
  lcd.clear();
  lcd.print(String(test.getMoney()));
  
  delay(5000);
 
  
  
  
  /*
  int x;
  x = analogRead (0);
  lcd.setCursor(10,1);
  
  if (x < 60)        {lcd.print("Right ");  }
  else if (x < 200)  {lcd.print ("Up    "); }
  else if (x < 400)  {lcd.print ("Down  "); }
  else if (x < 600)  {lcd.print ("Left  "); }
  else if (x < 800)  {lcd.print ("Select"); }
  */
}
