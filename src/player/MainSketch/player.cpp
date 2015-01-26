#include "player.h"

//---------------------------------------------------------------------------------------------------------

player::player()
{
  // Initialise the variables
  m_button.setPin(0);
  m_money = 0;
  m_numCards = 0;
  m_maxNumCards = 0;
  
}

//---------------------------------------------------------------------------------------------------------

player::~player()
{

}

//---------------------------------------------------------------------------------------------------------

uint16_t player::placeBet(uint16_t _max, uint16_t _min)
{
   bool quit = false;
   bool fold = false;
   
   //check if they have enough money, other return FOLD.
   if(m_money < _min)
   {
     return BET::FOLD;  
   }
   
   //main betting loop
   while(!quit)
   {
     bool exit = false;
     bool showData = false;
     fold = false;
     
     //set bet to the min bet range.
     uint16_t bet = _min;
     
     lcd.clear();
     lcd.print("Place bet:");
     
     delay(500);
     
     while(!exit)
     {
      // updates value for button value.
      m_button.updateValue();
      
      // press right to return from seeing player data.
      if      (m_button.right())                                                  { lcd.clear();lcd.print("Place bet:");showData = false;    }
      
      // press left to see players data, money and cards.
      else if (m_button.left())                                                   { lcd.clear(); this->playerDataScreen(); showData = true;  }
      
      // press up whilst on the data screen to show name.
      else if (m_button.up() && showData == true )                                { lcd.clear(); m_display.displayName(getName());           }
      
      // press down to return back to money and cards from name.
      else if (m_button.down() && showData == true )                              { this->playerDataScreen();                                }
      
      // press up on the place bet screen to increase bet value. will not go beyond bet max or players own money.
      else if (m_button.up()   && bet < _max && bet < m_money && showData==false) { bet++; fold = false;                                     }
      
      // press down on place bet screen to decrease bet value.
      else if (m_button.down() && bet > _min && bet <= m_money && showData==false){ bet--; fold = false;                                     }
      
      // keep pressing down to get to FOLD
      else if (m_button.down() && bet == _min && showData==false)                 { fold = true;                                             }
      
      // press select whilst on bet screen to continue.
      else if (m_button.select() && showData == false)                            { exit = true;                                             }

      // have to use delay, not ideal to slow button press
      delay(125);

      // print the bet or fold
      lcd.setCursor(0,1);
      if(fold == true && showData == false)       { lcd.print("FOLD");      }
      else if(fold == false && showData == false) { lcd.print(String(bet)+"       "); }
      
     }

     lcd.clear();
     
     // ask to confirm choice and the return the appropriate value.
     if(fold == true)      { lcd.print("FOLD?:");                         }  
     else if(fold == false){ lcd.print("Confirm: "+String(bet))+"?";  }
      
     bool confirm = m_button.menuYesNo(1);

     if(confirm == true)
     {
       quit=true;
       if(fold == true)  { return BET::FOLD; }
       else              { m_money = m_money - bet; return bet; }
    }
  }
}

//---------------------------------------------------------------------------------------------------------

void player::receiveMoney(uint16_t _money)
{
    // Add money to players money
    m_money = m_money + _money;
    
    // display winner message.
    m_display.winner(_money);

}

//---------------------------------------------------------------------------------------------------------

void player::setMoney(uint16_t _money)
{
  m_money = _money;
}

//---------------------------------------------------------------------------------------------------------
	
void player::receiveCard(uint8_t _cards[])
{
  //if not reached max card limit, receive card
  if(m_numCards < m_maxNumCards)
  {
    m_cards[m_numCards].rank = _cards[0];
    m_cards[m_numCards].suit = _cards[1];
    m_numCards++;
  }  
  else
  {
    // maybe print max card limit reached.
    return;
  }
}

//---------------------------------------------------------------------------------------------------------

void player::setName()
{
    bool exit = false;
    
    while( !exit )
    {
        char alphabet [ 27 ] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        int index = 26;
        int currentPosX = 0;
        int currentPosY = 1;
        int nLetters = 1;
        char tmp[ 15 ];
        
        lcd.clear();
        bool select = false;
        
        while( !select )
        {
            lcd.setCursor( 0, 0 );
            lcd.print( "Enter Name:" );
            m_button.updateValue();
            lcd.setCursor( currentPosX, currentPosY );
            
            //shift cursor of one position to the right
            if ( m_button.right() ) 
            {
                currentPosX += 1;
                lcd.setCursor( currentPosX, currentPosY );
                //start again the alphabet
                index = 26;
                delay( 400 );
                //count letters in the name
                ++nLetters;
            }
            else if ( m_button.up() ) 
            {   
                //up through the alphabet, checks if Z is reached to start again from A
                if ( alphabet[ index ] == 'Z'|| alphabet[ index ] == '\0' ) { index = 0; }
                else { index+=1; }
                lcd.print( alphabet[ index ] );
                tmp[ currentPosX ] = alphabet[ index ];
                delay( 400 );
            }
            else if ( m_button.down() ) 
            {
                //down through the alphabet, checks if A is reached to start again from Z
                if ( alphabet[ index ] == 'A'|| alphabet[ index ] == '\0' ) { index = 25; }
                else { index-=1; }
                lcd.print( alphabet[ index ] );
                tmp[ currentPosX ] = alphabet[ index ];
                delay( 400 );
            }
            else if ( m_button.left() ) //shift cursor of one position to the left
            {
                currentPosX -= 1;
                lcd.setCursor(currentPosX,currentPosY);
                delay( 400 );
            }
            else if ( m_button.select() ) { select = true; }
        }
        
        // copy name just set to m_playerName array
        for ( int i = 0; i < nLetters; ++i )
        {
            m_playerName[ i ] = tmp[ i ];
        }
        
        //confirm name
        lcd.clear();
        lcd.print( "Confirm: "+ String( m_playerName ) );
        
        bool confirm = m_button.menuYesNo(1);
        
        if( confirm )
        {
            lcd.clear();
            lcd.print( "Welcome " + String( m_playerName ) + "!" );
            delay( 2000 );
            exit = true;
        }   
    }
}

//---------------------------------------------------------------------------------------------------------

void player::resetPlayer(uint16_t _money)
{
    m_money = _money;
    this->resetCards();
}

//---------------------------------------------------------------------------------------------------------

void player::resetCards()
{
    for ( int i = 0; i < m_numCards; ++i )
    {
      m_cards[ i ].suit = 0;
      m_cards[ i ].rank = 0;
    }
    
    m_numCards = 0;
}

//---------------------------------------------------------------------------------------------------------

void player::joinGame()
{
  bool play = false;
  
  lcd.clear();
  
  lcd.print("Join game?:");
   
  play = m_button.menuYesNo(1);
  
  if(play == true)
  {
    return;
  }
  else if(play == false)
  {
    m_display.screenReset();
  }
}

//---------------------------------------------------------------------------------------------------------    

void player::playerDataScreen()
{ 
  m_display.displayCards(0, m_numCards, m_cards);
  m_display.displayMoney(1, m_money);
}

//---------------------------------------------------------------------------------------------------------

void player::setMaxCardLimit(uint8_t _max)
{
   m_maxNumCards = _max; 
}
    
