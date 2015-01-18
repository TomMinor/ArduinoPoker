#include "player.h"

player::player(uint16_t _money, uint8_t _cardNum)
{
    m_money = _money;
    m_numCards = _cardNum;
  
}

player::~player()
{

}

uint16_t player::placeBet(uint16_t _max, uint16_t _min)
{
   bool quit = false;
   input button(0);

   //need to find a better way of not hardcoding the pin number.
   while(!quit)
   {
     bool exit = false;
     
     uint16_t bet = _min;
     uint8_t x;

     lcd.clear();

     lcd.print("Place bet:");

     //fixes it from selecting autimatically needs better fix.
     delay(1000);

     while(!exit)
     {
      button.updateValue();
      lcd.setCursor(0,1);

      if      (button.right() && bet <= (_max-10) && bet < (m_money-10))  { bet+=10;    }
      else if (button.up() && bet < _max && bet < m_money)                { bet++;      }
      else if (button.down() && bet > _min && bet < m_money)              { bet--;      }
      else if (button.left() && bet >= (_max+10) && bet < (m_money+10))   { bet-=10;    }
      else if (button.select())                                           { exit = true;}

      // have to use delay, no ideal
      delay(125);

      // print the bet
      lcd.print(String(bet));
     }

     lcd.clear();
     lcd.print("Confirm bet: "+String(bet));
      
     
     bool confirm = button.menuYesNo(1);

     if(confirm == true)
     {
       quit = true;
       m_money = m_money - bet;
       return bet;
     }
  }
}

void player::receiveMoney(uint16_t _money)
{
    m_money = m_money + _money;
}

void player::receiveCard()
{

}

void player::setName()
{
    input button (0);
    bool exit = false;
    
    while(!exit)
    {
        char alphabet [27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','\0'};
        int index = 26;
        int currentPosX = 0;
        int currentPosY = 1;
        bool setName = true;
        int nLetters = 1;
        char tmp[16];
        lcd.clear();
        lcd.print("Enter Name:");
        lcd.setCursor(currentPosX, currentPosY);
        
        while(setName)
        {
            button.updateValue();
            lcd.setCursor(currentPosX,currentPosY);
            
            if (button.right()) {
                currentPosX += 1;
                lcd.setCursor(currentPosX,currentPosY);
                index = 26;
                delay(400);
                ++nLetters;
            }
            else if (button.up()) {
                if(alphabet[index] == 'Z'|| alphabet[index] == '\0'){
                    index = 0;
                }
                else{
                    index+=1;
                }
                lcd.print(alphabet[index]);
                tmp[currentPosX] = alphabet[index];
                delay(400);
                
            }
            else if (button.down()){
                if(alphabet[index] == 'A'|| alphabet[index] == '\0'){
                    index = 25;
                }
                else{
                    index-=1;
                }
                lcd.print(alphabet[index]);
                tmp[currentPosX] = alphabet[index];
                delay(400);
            }
            else if (button.left()){
                currentPosX -= 1;
                lcd.setCursor(currentPosX,currentPosY);
                delay(400);
            }
            else if (button.select()){
                for( int i = 0; i < nLetters; ++i)
                {
                    m_playerName[i] = tmp[i];
                }
                setName = false;
            }
            
        }
        
        lcd.clear();
        lcd.print("Confirm: "+ String(m_playerName));
        
        bool confirm = button.menuYesNo(1);
        
        if(confirm == true)
        {
            lcd.clear();
            lcd.print("Welcome " +String(m_playerName)+"!");
            delay(2000);
            exit = true;
        }
    }
    
}

char* player::getName()
{
    return m_playerName;
}


void player::resetPlayer(uint16_t _money, uint16_t _cardNum)
{
    m_money = _money;
    m_numCards = _cardNum;
}

void player::resetCards()
{

}

