#include <LiquidCrystal.h>
#include "pokerDisplay.h"
#include "player.h"
#include "input.h"
#include "card.h"

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
uint8_t cards[6]={byte(Rank::SIX), Suit::SPADE, byte(Rank::KING), Suit::DIAMOND, byte(Rank::ACE), Suit::CLUB};
unsigned int bet=0;
bool betState=true;
bool recieved=false;


LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

player test;



void setup() 
{
  lcd.begin(16,2);
}

  /*
  Serial.begin(9600);
  d.createCustomChar();
  */

void loop() 
{
       test.resetPlayer(200, 3); 
     
     test.receiveCard(0, cards);
     test.receiveCard(1, cards);
     test.receiveCard(2, cards);
     
     test.placeBet(200, 100);
     
     delay(3000);
}

  /*
  while(recieved!=true)
  {
    //code to test input
    //test.setName();
    //Serial.print(test.getName());
    if (getHeader(cards))
      {  
        Serial.write("Data Sent \n");
        lcd.clear();
        lcd.print("Data Processed");
        recieved=true;
        
                
      }
           
    Serial.write("listening \n");
    
    lcd.clear();
    d.displayCard(cards[0], cards[1], 1, 0, 1);
    d.displayCard(cards[2], cards[3], 4, 0, 2);
    delay(2000);
     
  }
  if(betState!=false)
    {     
        
        do
        {
          bet=test.placeBet(100, 50);            
        }while(bet!=0); 
        
        lcd.clear();
        Serial.print("Disconnected");
        lcd.print("You Folded");
        delay(1000);
        exit(0); 
     }
     */
     /*
     test.resetPlayer(200, 3); 
     
     test.receiveCard(0, cards);
     test.receiveCard(1, cards);
     test.receiveCard(2, cards);
     
     test.placeBet(200, 100);
     
     delay(3000);
     */


