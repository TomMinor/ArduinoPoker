#include <LiquidCrystal.h>
#include "player.h"
#include "pokerDisplay.h"
#include "input.h"
#include "card.h"


//card array that stores 2 bytes {card1,card2}
uint8_t cards[6]={Rank::SIX, Suit::SPADE, byte(Rank::ACE), Suit::CLUB, };
//unsigned int bet=0;
//bool betState=true;
//bool recieved=false;


LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

player player;

data coms;
uint8_t a= U16_TO_BYTE_L(0xff0f);
uint8_t b= U16_TO_BYTE_H(0xff0f);
void setup() 
{

  lcd.begin(16,2);
  Serial.begin(9600);
  player.joinGame();
//  
//  //player.setMoney(100);
  coms.limit_L = 50;
coms.limit_H = 80;
//  //player.receiveCard(cards);
//  //player.receiveCard(cards);
//  lcd.clear();
}


  
void loop() 
{
   
//   Serial.print("\n");
//   Serial.print(0xff0f,HEX);
//   Serial.print("\n");
//   Serial.print("\n");
//   Serial.print(a,HEX),
//   Serial.print("\n");
//   Serial.print(b,HEX),
//   Serial.print("\n");
//   Serial.print((((uint8_t)b<<8)|a),HE),
//   delay(500);
  //lcd.clear();
  uint8_t state;
  
  if(player.getMoney() == 0)
  {
    lcd.setCursor(0,0);
    lcd.print("Waiting for ");
    lcd.setCursor(0,1);
    lcd.print("money. ");
  }
  else if(player.checkFirstCard() == false)
  {
    lcd.setCursor(0,0);
    lcd.print("Waiting for ");
    lcd.setCursor(0,1);
    lcd.print("cards. ");
  }
  else
  {
    
    player.playerDataScreen();
  }
  
 
  
  state = getData(coms);
  
  switch(state)
  {
    case DEALER_CALLS::SET_CARDS:
    {
      player.receiveCard(coms.cards);
      break;
    }
    case DEALER_CALLS::SET_NAME:
    {
      player.setName();
      char* playerName = player.getName();
      sendName(playerName);
      break;
    }
    case DEALER_CALLS::SET_MONEY:
    {
      player.setMoney(coms.money);
      
      break;
    }
    case DEALER_CALLS::INITIATE_BET:
    {
      uint16_t bet = 0;
      bet = player.placeBet(coms.limit_H, coms.limit_L);
      lcd.clear();
      sendBet(bet);
      //delay(1000);   
      break;
    }
    case DEALER_CALLS::WIN_MONEY:
    {
      player.receiveMoney(coms.wMoney);
      break;
    }
    case DEALER_CALLS::RESET_CARDS:
    {
      
      player.resetCards();
      lcd.clear();
      break;
    }
    case DEALER_CALLS::RESET_PLAYER:
    {
      player.resetPlayer(coms.money);
      lcd.clear();
      break;
    }
    default:
    {
      break;
    }
  }
  
  
  
}



