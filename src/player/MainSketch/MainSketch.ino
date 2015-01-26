#include <LiquidCrystal.h>
#include "player.h"
#include "pokerDisplay.h"
#include "input.h"
#include "card.h"

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
  
  //intialise state variable
  uint8_t state;
 
  // show player data
  player.playerDataScreen();
  
 
  // get the state from comms.
  state = getData(coms);
  
  // decided what to do depending on state
  switch(state)
  {
    // gives a card to the player.
    case DEALER_CALLS::SET_CARDS:
    {
      player.receiveCard(coms.cards);
      break;
    }
    // calls the setName functions and then returns the name to comms.
    case DEALER_CALLS::SET_NAME:
    {
      player.setName();
      char* playerName = player.getName();
      sendName(playerName);
      break;
    }
    // sets the plays amount of money.
    case DEALER_CALLS::SET_MONEY:
    {
      player.setMoney(coms.money);
      break;
    }
    // asks the player to place a bet and then returns the bet to comms.
    case DEALER_CALLS::INITIATE_BET:
    {
      uint16_t bet = 0;
      bet = player.placeBet(coms.limit_H, coms.limit_L);
      lcd.clear();
      sendBet(bet);
      //delay(1000);   
      break;
    }
    // passes money to the player which is added to their total amount of money
    case DEALER_CALLS::WIN_MONEY:
    {
      player.receiveMoney(coms.wMoney);
      break;
    }
    // sets all cards to zero
    case DEALER_CALLS::RESET_CARDS:
    {
      
      player.resetCards();
      lcd.clear();
      break;
    }
    // resets player with a new amount of money. clears cards.
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



