#include <LiquidCrystal.h>
#include "pokerDisplay.h"
#include "player.h"
#include "input.h"
/**To George and Michelle*
To test the code first send 18 through the serial Monitor
then input the 22 for the first packet 
then input the same again
22 represents diamond 7
You should see your cards for abit the go into a betting state
When you set a bet, it will be reflected on the Serial manager
When you fold you will be disconnected

*/
//card array that stores 2 bytes {card1,card2}
uint8_t cards[4]={0,0,0,0};
unsigned int bet=0;
bool betState=true;
bool recieved=false;


LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

display d(1);
player test(80, 2);

;

void setup() 
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16,2);
  Serial.begin(9600);
  d.createCustomChar();
  
}


void loop() 
{
  
  while(recieved!=true)
  {
    if (getHeader(cards))
      {  
        Serial.write("Data Sent \n");
        lcd.clear();
        lcd.print("Data Processed");
        recieved=true;
        delay(1000);
        
      }
      else
      {
      
      
      Serial.write("listening \n");
      lcd.clear();
      lcd.print("listening");
      }  
      lcd.clear();
      d.displayCard(cards[2], cards[3], 1, 0, 1);
      delay(1000);
   }
   
   
   if(betState!=false)
   {
      
     
        lcd.print(String(bet));
        betState,bet=test.placeBet(100, 50);
        lcd.clear();
        
        test.sendData(bet,2,"int");
        if (bet==0)
        {
          betState=false;
        }
       
      
   }
   else
   {
      lcd.clear();
      Serial.print("Disconnected");
      lcd.print("You Folded");
      delay(1000);
      exit(0);
      
   }
  

  
  }

