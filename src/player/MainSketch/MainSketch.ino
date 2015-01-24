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

data        coms;
playerData  player_coms;

void setup() 
{
   
   lcd.begin(16,2);
   Serial.begin(9600);
   
}

  
 
 
  

void loop() 
{
  
}

 

