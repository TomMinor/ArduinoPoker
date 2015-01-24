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

player player;

data coms;

void setup() 
{

  lcd.begin(16,2);
  Serial.begin(9600);
  player.joinGame();
   
}


  
void loop() 
{

  lcd.clear();
  
  if(player.getMoney() == 0)
  {
    lcd.setCursor(0,0);
    lcd.print("Waiting for ");
    lcd.setCursor(0,1);
    lcd.print("money.");
  }
  else if(player.checkFirstCard() == false)
  {
    lcd.setCursor(0,0);
    lcd.print("Waiting for ");
    lcd.setCursor(0,1);
    lcd.print("cards.");
  }
  else
  {
    player.showPlayerData();
  }
  
  uint8_t state;
  
  state = getData(coms);
  
  switch(state)
  {
    case DEALER_CALLS::SET_CARDS:
    {
      player.receiveCard(0, coms.cards);
      player.receiveCard(1, coms.cards);
      break;
    }
    case DEALER_CALLS::SET_NAME:
    {
      player.setName();
      //char playerName[15] = player.getName();
      break;
    }
    case DEALER_CALLS::SET_MONEY:
    {
      player.setMoney(coms.money);
      Serial.print(coms.money);
      break;
    }
    case DEALER_CALLS::INITIATE_BET:
    {
      uint16_t bet = 0;
      bet = player.placeBet(coms.limit_H, coms.limit_L);
      //sendData(bet)
      break;
    }
    case DEALER_CALLS::WIN_MONEY:
    {
      player.receiveMoney(coms.wMoney);
      player.winner();
      break;
    }
    case DEALER_CALLS::RESET_CARDS:
    {
      player.resetCards();
      break;
    }
    case DEALER_CALLS::RESET_PLAYER:
    {
      player.resetPlayer(coms.money);
      break;
    }
    default:
    {
      break;
    }
  }
  
  
  
}



