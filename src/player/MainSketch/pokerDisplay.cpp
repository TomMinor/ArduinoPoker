#include "pokerDisplay.h"

display::display()
{
}

display::~display()
{

}


void display::createCustomChar()
{
    //Custom characters created using http://omerk.github.io/lcdchargen/
    
    byte diamond[8] = {
        0b00000,
        0b00100,
        0b01110,
        0b11101,
        0b11101,
        0b01110,
        0b00100,
        0b00000
    };
    
    byte heart[8] = {
        0b00000,
        0b01010,
        0b11111,
        0b11111,
        0b11111,
        0b01110,
        0b00100,
        0b00000
    };
    
    byte club[8] = {
        0b01010,
        0b00100,
        0b10101,
        0b11111,
        0b10101,
        0b00100,
        0b01110,
        0b00000
    };
    
    byte spade[8] = {
        0b00000,
        0b00100,
        0b01110,
        0b11111,
        0b11111,
        0b01110,
        0b10101,
        0b00000
    };
    
    lcd.createChar(0, diamond);
    lcd.createChar(1, heart);
    lcd.createChar(2, club);
    lcd.createChar(3, spade);
    
}

/** Tom's idea
enum Types { CARD, BET, BETLIMITS, NAME };

sendData(CARD, MyCard);
sendData(BETLIMITS, Min, Max);

sendData(MyCard, ..)
{
   switch(MyCard)
   {
     case CARD:
     {
       //read in next argument
     }
     
     case BETLIMITS:
     {
       //read in next 2 arguments
     }
   }
}
**/

void display::displayCard(uint8_t _rank, uint8_t _suit, int _x, int _y, int _nCard, int _totCards)
{
    
    m_x = _x;
    m_y = _y;
   
   switch(_suit) {
     case Suit::DIAMOND:
       lcd.setCursor( m_x, m_y );
       lcd.write( byte( 0 ) );
       break;
     case Suit::HEART:
       lcd.setCursor( m_x, m_y );
       lcd.write( 1 );
       break;
     case Suit::CLUB:
       lcd.setCursor(m_x,m_y);
       lcd.write(2);
       break;
     case Suit::SPADE:
       lcd.setCursor(m_x,m_y);
       lcd.write(3);
       break;
     default:
       lcd.clear();
       lcd.setCursor(0,1);
       lcd.print("No valid suit.");
       delay(1000);
   }
     
    switch(_rank) {
     case byte(Rank::TWO):
       lcd.setCursor(m_x+1,m_y);
       lcd.print("2");
       break;
     case byte(Rank::THREE):
       lcd.setCursor(m_x+1,m_y);
       lcd.print("3");
       break;
     case byte(Rank::FOUR):
       lcd.setCursor(m_x+1,m_y);
       lcd.print("4");
       break;
     case byte(Rank::FIVE):
       lcd.setCursor(m_x+1,m_y);
       lcd.print("5");
       break;
     case byte(Rank::SIX):
       lcd.setCursor(m_x+1,m_y);
       lcd.print("6");
       break;
     case byte(Rank::SEVEN):
       lcd.setCursor(m_x+1,m_y);
       lcd.print("7");
       break;
     case byte(Rank::EIGHT):
       lcd.setCursor(m_x+1,m_y);
       lcd.print("8");
       break;
      case byte(Rank::NINE):
       lcd.setCursor(m_x+1,m_y);
       lcd.print("9");
       break;
     case byte(Rank::TEN):
       lcd.setCursor(m_x+1,m_y);
       lcd.print("T");
       break;
     case byte(Rank::JACK):
       lcd.setCursor(m_x+1,m_y);
       lcd.print("J");
       break;
     case byte(Rank::QUEEN):
       lcd.setCursor(m_x+1,m_y);
       lcd.print("Q");
       break;
     case byte(Rank::KING):
       lcd.setCursor(m_x+1,m_y);
       lcd.print("K");
       break;
     case byte(Rank::ACE):
       lcd.setCursor(m_x+1,m_y);
       lcd.print("A");
       break;
     default:
       lcd.clear();
       lcd.setCursor(0,1);
       lcd.print("No valid rank.");
       delay(1000);
   }
   
    if(_nCard != _totCards)
    {
        lcd.setCursor(_x+2,0);
        lcd.print("|");
    }
   
}


void display::waitCards()
{
  lcd.clear();
  lcd.print( " Waiting cards" );
  
  int pos = 6;
  for( int i = 0; i < 3 ; ++i )
  {
    for ( int posCounter = 0; posCounter < 3; ++posCounter )
    {
      lcd.setCursor( pos, 1 );
      lcd.print( "." );
      ++pos;
      delay( 700 );
    }
    pos = 6;
    lcd.setCursor( pos, 1);
    lcd.print("   ");
    delay(200);
    
  }
}
