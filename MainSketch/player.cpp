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

}

void player::resetPlayer(uint16_t _money, uint16_t _cardNum)
{
    m_money = _money;
    m_numCards = _cardNum;
}

void player::resetCards()
{

}

