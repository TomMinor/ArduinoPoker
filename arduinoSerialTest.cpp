// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8,9,4,5,6,7);

// These are broken for now
//enum class Suit : uint8_t { SPADE, HEART, DIAMONDS, CLUB, UNKNOWN_SUIT };
//enum class Rank : uint8_t { ACE = 0, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, UNKNOWN_RANK };

enum SerialFlags { CARD, MONEY, PLAYERSTATE, GAMESTATE };
enum GameState { PLAYING, DEALING, RESET };
enum Suit { SPADE, HEART, DIAMONDS, CLUB, UNKNOWN_SUIT };
enum Rank { ACE = 0, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, UNKNOWN_RANK };

String suitToString[] = {
  "SPADE",
  "HEART",
  "DIAMONDS",
  "CLUB",
  "SUITERROR"
};

String rankToString[] = { 
  "ACE",
  "TWO",
  "THREE",
  "FOUR",
  "FIVE",
  "SIX",
  "SEVEN",
  "EIGHT",
  "NINE",
  "TEN",
  "JACK",
  "QUEEN",
  "KING",
  "RANKERROR"
};

uint16_t money = 0;
GameState state = PLAYING;
Suit suit = UNKNOWN_SUIT;
Rank rank = UNKNOWN_RANK;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  Serial.begin(9600);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);

   // Expect [FLAG][DATA]
   // * Card  : CARD[suit][rank]
   // * Money : MONEY[value]
   // * PlayerState : PLAYERSTATE[state]
   // * GameState : GAMESTATE[state]
   if(Serial.available() > 0)
   {
     uint8_t dataFlag = Serial.parseInt();;

     switch(state)
     {
       case CARD:  /* "CARD,SPADE,TWO" or "0,0,1" */
       {
         // Recieve and verify suit
         uint8_t incomingByte = Serial.parseInt();
         
         suit = (Suit)incomingByte;
         if(suit > 3)
         {
           Serial.println("ERROR : Suit number " + String(suit) + "is not valid.");
           suit = UNKNOWN_SUIT;
         }
         
         /* Recieve and verify rank */
         incomingByte = Serial.parseInt();
         
         rank = (Rank)incomingByte;
         if(rank > KING)
         {
           Serial.println("ERROR : Suit number " + String(rank) + "is not valid");
           rank = UNKNOWN_RANK;
         }
         break;
       }
         
       case MONEY: /* "MONEY,[int8_t],[int8_t] <- 2 parts */
       {
         // Recieve the two parts of the int16
         uint8_t partA = Serial.parseInt();
         uint8_t partB = Serial.parseInt();
         
         // Combine them
         uint16_t result = partA | (partB << 8);
         
         money = result;
         
         break;
       }
         
       case PLAYERSTATE: /* PLAYERSTATE,0, */
       {
         // NOT IMPLEMENTED
         // playerState = Serial.parseInt();

         break;
       }
         
       case GAMESTATE:
       {
         // Recieve and verify suit
         state = (GameState)Serial.parseInt();

         break;
       }
     }
   }     
  
  lcd.print(String(suitToString[suit]) + "," + String(rankToString[rank]));
}
