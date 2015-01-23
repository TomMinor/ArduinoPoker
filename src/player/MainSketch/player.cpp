#include "player.h"


player::player()
{
 
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
     //return fold;
   }
   
   
   input button(0);


   while(!quit)
   {
     bool exit = false;
     fold = false;
     bool showData = false;
     
     uint16_t bet = _min;

     lcd.clear();

     lcd.print("Place bet:");

     delay(1000);

     while(!exit)
     {
      button.updateValue();
  
      if      (button.right())                                                  { lcd.clear();lcd.print("Place bet:");showData = false;    }
      else if (button.left())                                                   { this->showPlayerData(); showData = true;                 }
      else if (button.up()   && bet < _max && bet < m_money && showData==false) { bet++; fold = false;                                     }
      else if (button.down() && bet > _min && bet <= m_money && showData==false){ bet--; fold = false;                                     }
      else if (button.down() && bet == _min && showData==false)                 { fold = true;                                             }
      else if (button.select() && showData == false)                            { exit = true;                                             }

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
      
     bool confirm = button.menuYesNo(1);

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
}


void player::receiveCard( uint8_t _block, uint8_t _cards[] )
{

   
  uint8_t tmp = _block*2; 

  m_cards[_block].rank = _cards[tmp];
  m_cards[_block].suit = _cards[tmp+1];
        
   
    
}


void player::setName()
{
    input button (0);
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
            button.updateValue();
            lcd.setCursor( currentPosX, currentPosY );
            
            if ( button.right() ) {
                currentPosX += 1;
                lcd.setCursor( currentPosX, currentPosY );
                index = 26;
                delay( 400 );
                ++nLetters;
            }
            else if ( button.up() ) {
                
                if ( alphabet[ index ] == 'Z'|| alphabet[ index ] == '\0' ) { index = 0; }
                else { index+=1; }
                lcd.print( alphabet[ index ] );
                tmp[ currentPosX ] = alphabet[ index ];
                delay( 400 );
                
            }
            else if ( button.down() ) {
                
                if ( alphabet[ index ] == 'A'|| alphabet[ index ] == '\0' ) { index = 25; }
                else { index-=1; }
                lcd.print( alphabet[ index ] );
                tmp[ currentPosX ] = alphabet[ index ];
                delay( 400 );
                
            }
            else if ( button.left() ) {
                
                currentPosX -= 1;
                lcd.setCursor(currentPosX,currentPosY);
                delay( 400 );
                
            }
            else if ( button.select() ) { select = true; }
            
        }
        
        for ( int i = 0; i < nLetters; ++i )
        {
            m_playerName[ i ] = tmp[ i ];
        }
        
        lcd.clear();
        lcd.print( "Confirm: "+ String( m_playerName ) );
        
        bool confirm = button.menuYesNo(1);
        
        if( confirm )
        {
            lcd.clear();
            lcd.print( "Welcome " + String( m_playerName ) + "!" );
            delay( 2000 );
            exit = true;
        }
        
    }
    
}


void player::resetPlayer(uint16_t _money, uint16_t _cardNum)
{
    m_money = _money;
    m_numCards = _cardNum;
}


void player::resetCards()
{
    for ( int i = 0; i < m_numCards; ++i )
    {
      m_cards[ i ].suit = 0;
      m_cards[ i ].rank = 0;
    }
}

void player::showPlayerData()
{    
  lcd.clear();
  
  m_display.createCustomChar();
  
  lcd.print("Cards: ");
  for(int i = 0; i < m_numCards; ++i)
  {
    m_display.displayCard( m_cards[i].rank, m_cards[i].suit, 7+(3*i), 0, i+1, m_numCards );
  }
  
  lcd.setCursor(0,1);
  lcd.print("Money: "+String(m_money)); 
}

///@brief Comms sendData implementations

bool player::sendBet  (uint16_t  _data,uint8_t _datatype)
{
   uint8_t bytes[2];
   sendHeader(_datatype);
   
   while(!RecieveConfirmation())
   {
    sendHeader(_datatype);
   }
   
   
   bytes[0]=U16_TO_BYTE_H(_data);
   bytes[1]=U16_TO_BYTE_L(_data);
   
   for (int i=0;i<DATA::BET;i++)
   {
     Serial.write(bytes[i]);
   }
     
   return true;      
   
}
bool player::sendName (char _data[15],uint8_t _datatype)
{
  
  while(!RecieveConfirmation())
  {
    sendHeader(_datatype);
  }
  
  for (int i=0;i<DATA::NAME;i++)
  {
    Serial.print(_data[i]); 
  }
    
  return true;    

  
}

bool player::sendFold (bool  _data,uint8_t _datatype)
{
  sendHeader(_datatype);
  while(!RecieveConfirmation())
  {
   sendHeader(_datatype);
  }
   Serial.write(_data);
    
   return true; 
  
}



//Coms header packer and sender
void player::sendHeader(uint8_t _datatype)
{
  uint8_t header=0;
  switch(_datatype)
     {
      case PLAYER_SENDS::NAME:     //HEADER FOR SENDING BET_AMT 
           header=NAME<<4|DATA::NAME;
           Serial.write(header);
           break;
      
      case PLAYER_SENDS::BET:    //HEADER FOR SENDING BET_AMT 
           header=BET_AMT<<4|DATA::BET;
           Serial.write(header);
           break;
      
      case PLAYER_SENDS::FOLD:      //HEADER FOR SENDING NAME
           header=BET_AMT<<4|DATA::BOOL;
           Serial.write(header);
           break;    
      
           default:
           break;
     }
  
}

bool player::RecieveConfirmation()
{ 
  bool success=0;
  while(Serial.available()>0)
  {
     success=Serial.read();   
  }
  return success;
}  
    

    
