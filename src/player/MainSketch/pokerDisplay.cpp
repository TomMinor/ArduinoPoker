#include "pokerDisplay.h"

//---------------------------------------------------------------------------------------------------------

display::display()
{
  this->createCustomChar();
}

//---------------------------------------------------------------------------------------------------------

display::~display()
{

}

//---------------------------------------------------------------------------------------------------------

void display::createCustomChar()
{
    //Creating custom char using http://omerk.github.io/lcdchargen/
    
    byte diamond[8] = 
    {
        0b00000,
        0b00100,
        0b01110,
        0b11101,
        0b11101,
        0b01110,
        0b00100,
        0b00000
    };
    
    byte heart[8] = 
    {
        0b00000,
        0b01010,
        0b11111,
        0b11111,
        0b11111,
        0b01110,
        0b00100,
        0b00000
    };
    
    byte club[8] = 
    {
        0b01010,
        0b00100,
        0b10101,
        0b11111,
        0b10101,
        0b00100,
        0b01110,
        0b00000
    };
    
    byte spade[8] = 
    {
        0b00000,
        0b00100,
        0b01110,
        0b11111,
        0b11111,
        0b01110,
        0b10101,
        0b00000
    };
    
    lcd.createChar( 0, diamond );
    lcd.createChar( 1, heart   );
    lcd.createChar( 2, club    );
    lcd.createChar( 3, spade   );
    
}

//---------------------------------------------------------------------------------------------------------

void display::displayMoney(uint8_t _line, uint16_t _money)
{
  lcd.setCursor(0, _line);
  
  lcd.print("Money: ");
  
  if(_money == 0)
  {
    lcd.print("NO MONEY");
  }
  else
  {
    // poorly hacked together
    lcd.print("$"+String(_money)+"    ");
  }

}

//---------------------------------------------------------------------------------------------------------

void display::displayName(char* _name)
{
  lcd.clear();
  lcd.print("Name:");
  lcd.setCursor(0,1);
  lcd.print(_name);
}

//---------------------------------------------------------------------------------------------------------

void display::displayCard( uint8_t _rank, uint8_t _suit, int _x, int _y, int _nCard, int _totCards )
{

  // Compare _suit value and print corresponding card suit
  
   switch( _suit ) 
   {
     case Suit::DIAMOND:
     {
       lcd.setCursor( _x, _y );
       lcd.write( byte( 0 ) );
       break;
     }
     case Suit::HEART:
     {
       lcd.setCursor( _x, _y );
       lcd.write( 1 );
       break;
     }
     case Suit::CLUB:
     {
       lcd.setCursor( _x, _y );
       lcd.write( 2 );
       break;
     }
     case Suit::SPADE:
     {
       lcd.setCursor( _x, _y );
       lcd.write( 3 );
       break;
     }
     default:
     {
       lcd.clear();
       lcd.print( "No valid suit." );
       delay( 1000 );
     }
   }
     
   // Compare _rank value and print corresponding card rank
   
   switch( _rank ) 
   {
     case byte( Rank::TWO ):
     {
       lcd.setCursor( _x + 1, _y );
       lcd.print( "2" );
       break;
     }
     case byte( Rank::THREE ):
     {
       lcd.setCursor( _x + 1, _y );
       lcd.print( "3" );
       break;
     }
     case byte( Rank::FOUR ):
     {
       lcd.setCursor( _x + 1, _y );
       lcd.print( "4" );
       break;
     }
     case byte( Rank::FIVE ):
     {
       lcd.setCursor( _x + 1, _y );
       lcd.print( "5" );
       break;
     }
     case byte( Rank::SIX ):
     {
       lcd.setCursor( _x + 1, _y );
       lcd.print( "6" );
       break;
     }
     case byte( Rank::SEVEN ):
     {
       lcd.setCursor( _x + 1, _y );
       lcd.print( "7" );
       break;
     }
     case byte( Rank::EIGHT ):
     {
       lcd.setCursor( _x + 1, _y );
       lcd.print( "8" );
       break;
     }
     case byte( Rank::NINE ):
     {
       lcd.setCursor( _x + 1, _y );
       lcd.print( "9" );
       break;
     }
     case byte( Rank::TEN ):
     {
       lcd.setCursor( _x + 1, _y );
       lcd.print( "T" );
       break;
     }
     case byte( Rank::JACK ):
     {
       lcd.setCursor( _x + 1, _y );
       lcd.print( "J" );
       break;
     }
     case byte( Rank::QUEEN ):
     {
       lcd.setCursor( _x + 1, _y );
       lcd.print( "Q" );
       break;
     }
     case byte( Rank::KING ):
     {
       lcd.setCursor( _x + 1, _y );
       lcd.print( "K" );
       break;
     }
     case byte( Rank::ACE ):
     {
       lcd.setCursor( _x + 1, _y );
       lcd.print( "A" );
       break;
     }
     default:
     {
       lcd.clear();
       lcd.print( "No valid rank." );
       delay( 1000 );
     }
   }
   
   // Print a vertical bar after card to separate it from the following one
   
   if(_nCard != _totCards)
   {
     lcd.setCursor( _x + 2, 0 );
     lcd.print( "|" );
   }
   
}

//---------------------------------------------------------------------------------------------------------

bool display::checkForCard(card _card)
{
  if(_card.suit == 0 || _card.rank == 0)
  {
    return false;
  }
  else 
  {
    return true;
  }
}

//---------------------------------------------------------------------------------------------------------

void display::displayCards(uint8_t _line, uint8_t _numCards,card _cards[])
{  
  lcd.setCursor(0, _line);  
  lcd.print("Cards: ");
  
  // check if there is first card, if true, display it
  
  if(checkForCard(_cards[0]) == true)
  {
    displayCard( _cards[0].rank, _cards[0].suit, 7, 0, 1, _numCards);
    
    // go on checking other possible cards in the array and display them
    
    for(int i = 1; i < _numCards; ++i)
    {
      if(checkForCard(_cards[i]) == true)
      {
        displayCard( _cards[i].rank, _cards[i].suit, 7+(3*i), 0, i+1, _numCards);
        lcd.print("    ");
      }
    }
  }
  else
  {
    lcd.print("NO CARDS");
  }
}


//---------------------------------------------------------------------------------------------------------

void display::winner(uint16_t _money)
{
  lcd.clear();
  
  lcd.print("You won $"+String(_money));
  delay(1500);
  
  lcd.clear();
  
  lcd.print("Winner Winner!");
  lcd.setCursor(0,1); 
  lcd.print("Chicken Dinner!");
  
  delay(1500);

}

//---------------------------------------------------------------------------------------------------------

void display::screenReset()
{
  lcd.clear();
  lcd.print("Hit reset");
  lcd.setCursor(0,1);
  lcd.print("to try again.");
}

//---------------------------------------------------------------------------------------------------------

