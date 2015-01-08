#include "player.h"

player::player(unsigned int _money, int _cardNum)
{
    m_money = _money;
    m_currentHandNum = _cardNum;
}

player::~player()
{

}

unsigned int player::placeBet(unsigned int _max, unsigned int _min)
{
   bool quit = false;
   button but(0);

   //need to find a better way of not hardcoding the pin number.
   while(!quit)
   {
     bool exit = false;
     bool confirm = false;
     unsigned int bet = _min;
     int x;

     lcd.clear();

     lcd.print("Place bet:");

     //fixes it from selecting autimatically needs better fix.
     delay(1000);

     while(!exit)
     {
      but.updateValue();
      lcd.setCursor(0,1);

      if      (but.right() && bet <= (_max-10) && bet < (m_money-10))  { bet+=10;    }
      else if (but.up() && bet < _max && bet < m_money)                { bet++;      }
      else if (but.down() && bet > _min && bet < m_money)              { bet--;      }
      else if (but.left() && bet >= (_max+10) && bet < (m_money+10))   { bet-=10;    }
      else if (but.select())                                           { exit = true;}

      // have to use delay, no ideal
      delay(125);

      // print the bet
      lcd.print(String(bet));
     }

     lcd.clear();
     lcd.print("Confirm bet: "+String(bet));
     char check = 0;

     while(!confirm)
     {
       but.updateValue();

       lcd.setCursor(0,1);
       lcd.print("yes:");

       lcd.setCursor(7,1);
       lcd.print("no:");

       if(but.right())
       {
         lcd.setCursor(5,1);
         lcd.print(" ");
         lcd.setCursor(11,1);
         lcd.print("X");
         if(check != 2) {check = 2;}
       }
       else if(but.left())
       {
         lcd.setCursor(5,1);
         lcd.print("X");
         lcd.setCursor(11,1);
         lcd.print(" ");
         if(check != 1) {check = 1;}
       }
       else if(but.select() && check==1)
       {
         confirm = true;
         quit = true;
         m_money = m_money - bet;
         return bet;
       }
       else if(but.select() && check==2)
       {
         break;
       }
     }
     ;
  }
}
