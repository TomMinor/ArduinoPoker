#include "player.h"


player::player()
{
  //hardcoded woop
  m_button.setPin(0);
  
  m_money = 0;
  
  m_numCards = 0;
  
}

player::~player()
{

}

uint16_t player::placeBet(uint16_t _max, uint16_t _min)
{
   bool quit = false;
   bool fold = false;
   
   
   //check if they have enough money, shouldnt happen.
   if(m_money < _min)
   {
     return BET::FOLD;  
   }
   
   while(!quit)
   {
     bool exit = false;
     bool showData = false;
     fold = false;
     uint16_t bet = _min;
     
     lcd.clear();

     lcd.print("Place bet:");
      
     delay(500);
     
     while(!exit)
     {
      m_button.updateValue();
  
      if      (m_button.right())                                                  { lcd.clear();lcd.print("Place bet:");showData = false;    }
      else if (m_button.left())                                                   { lcd.clear(); this->playerDataScreen(); showData = true;  }
      else if (m_button.up() && showData == true )                                { lcd.clear(); m_display.displayName(getName());           }
      else if (m_button.down() && showData == true )                              { this->playerDataScreen();                                }
      else if (m_button.up()   && bet < _max && bet < m_money && showData==false) { bet++; fold = false;                                     }
      else if (m_button.down() && bet > _min && bet <= m_money && showData==false){ bet--; fold = false;                                     }
      else if (m_button.down() && bet == _min && showData==false)                 { fold = true;                                             }
      else if (m_button.select() && showData == false)                            { exit = true;                                             }

      // have to use delay, not ideal
      delay(125);

      // print the bet or fold
      lcd.setCursor(0,1);
      if(fold == true && showData == false)       { lcd.print("FOLD");      }
      else if(fold == false && showData == false) { lcd.print(String(bet)+"       "); }
      
     }

     lcd.clear();
     
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


void player::receiveMoney(uint16_t _money)
{
    m_money = m_money + _money;
    m_display.winner(_money);

}

void player::setMoney(uint16_t _money)
{
  m_money = _money;
}

	
void player::receiveCard(uint8_t _cards[])
{
     
  //m_display.waitCards();
 
  //uint8_t tmp = (m_numCards*2);
   
  m_cards[m_numCards].rank = _cards[0];
  m_cards[m_numCards].suit = _cards[1];
     
  m_numCards++;
}




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
            
            if ( m_button.right() ) {
                currentPosX += 1;
                lcd.setCursor( currentPosX, currentPosY );
                index = 26;
                delay( 400 );
                ++nLetters;
            }
            else if ( m_button.up() ) {
                
                if ( alphabet[ index ] == 'Z'|| alphabet[ index ] == '\0' ) { index = 0; }
                else { index+=1; }
                lcd.print( alphabet[ index ] );
                tmp[ currentPosX ] = alphabet[ index ];
                delay( 400 );
                
            }
            else if ( m_button.down() ) {
                
                if ( alphabet[ index ] == 'A'|| alphabet[ index ] == '\0' ) { index = 25; }
                else { index-=1; }
                lcd.print( alphabet[ index ] );
                tmp[ currentPosX ] = alphabet[ index ];
                delay( 400 );
                
            }
            else if ( m_button.left() ) {
                
                currentPosX -= 1;
                lcd.setCursor(currentPosX,currentPosY);
                delay( 400 );
                
            }
            else if ( m_button.select() ) { select = true; }
            
        }
        
        for ( int i = 0; i < nLetters; ++i )
        {
            m_playerName[ i ] = tmp[ i ];
        }
        
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


void player::resetPlayer(uint16_t _money)
{
    m_money = _money;
    this->resetCards();
}


void player::resetCards()
{
    for ( int i = 0; i < m_numCards; ++i )
    {
      m_cards[ i ].suit = 0;
      m_cards[ i ].rank = 0;
    }
    
    m_numCards = 0;
}


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
    
bool player::checkFirstCard()
{
  if(m_cards[0].suit == 0 || m_cards[0].rank == 0)
  {
    return false;
  }
  else 
  {
    return true;
  }
}

void player::playerDataScreen()
{
  //lcd.clear();
  
  m_display.displayCards(0, m_numCards, m_cards);
  
  m_display.displayMoney(1, m_money);
 
}

    
