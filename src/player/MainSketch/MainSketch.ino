#include <LiquidCrystal.h>
#include "player.h"
#include "pokerDisplay.h"
#include "input.h"
#include "card.h"

// need to delete all test data.

//card array that stores 2 bytes {card1,card2}
//uint8_t card1[2]={Rank::SIX, Suit::SPADE};
//uint8_t card2[2]={Rank::ACE, Suit::CLUB};
//uint8_t card3[2]={Rank::EIGHT, Suit::HEART};


//unsigned int bet=0;
//bool betState=true;
//bool recieved=false;

// initialise global lcd.
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

//initialise player.
player player;

//initialise comms.
data coms;

uint8_t a= U16_TO_BYTE_L(0xff0f);
uint8_t b= U16_TO_BYTE_H(0xff0f);

void setup() 
{
  //set up lcd
  lcd.begin(16,2);
  //start serial
  Serial.begin(9600);
  
  //set player card limit to 2
  player.setMaxCardLimit(2);
  
  //ask player to join game.
  player.joinGame();
  
//player.setMoney(100);
//coms.limit_L = 50;
//coms.limit_H = 80;
//player.receiveCard(card1);
//player.receiveCard(card3);
//player.receiveCard(card2);

  //clear screen.
  lcd.clear();
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
//   lcd.clear();
  uint8_t state;
 
    
  player.playerDataScreen();
  
 
  
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



