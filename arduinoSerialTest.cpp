// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8,9,4,5,6,7);

uint8_t suit = 0;
uint8_t rank = 0;

//enum class Suit : uint8_t { SPADE, HEART, DIAMONDS, CLUB, UNKNOWN_SUIT };
//enum class Rank : uint8_t { ACE = 0, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, UNKNOWN_RANK };

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
  // print the number of seconds since reset:

   if(Serial.available() > 0)
   {
     suit = Serial.parseInt();
     if(suit > 3)
     {
       Serial.println("ERROR : Suit number " + String(suit) + "is not valid.");
       suit = UNKNOWN_SUIT;
     }

     rank = Serial.parseInt();
     if(rank > KING)
     {
       Serial.println("ERROR : Suit number " + String(rank) + "is not valid");
       rank = UNKNOWN_RANK;
     }

     Serial.println(String(suit) + "," + String(rank));
   }     

    /*if(Serial.available() > 0)
    {
      //incomingByte=Serial.read();
      Serial.println(String(Serial.available()));  
  
      tmp += char(incomingByte);
    }
    */
  
  lcd.print(String(suitToString[suit]) + "," + String(rankToString[rank]));
}
