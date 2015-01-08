// include the library code:
#include <LiquidCrystal.h>

// couple things just for testing
#define PlaceBet       1
#define ReceiveCard    2
#define Reset          3
#define SetName        4
#define GetName        5

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

class button
{
  public:
  
  button(){};
  ~button(){};
  
  boolean right(int _val)  
  {
      if(_val <= 60 )  {return true;} 
      return false;
  }
  boolean left(int _val)
    {
      if(_val <= 600 && _val >= 401)  {return true;} 
      return false;
  }
  boolean up(int _val)     
    {
      if(_val <= 200 && _val >= 61 )  {return true;} 
      return false;
  }
  boolean down(int _val)
    {
      if(_val <= 400 && _val >= 201)  {return true;} 
      return false;
  }
  boolean select(int _val)
    {
      if(_val <= 800 && _val >= 601)  {return true;} 
      return false;
  }
  
};

class player
{
private:
    unsigned int m_money;
    char m_playerName[];
    int m_currentHandNum;

  public:
    player(unsigned int _money, int _cardNum);
    ~player(){};

    boolean placeBet(unsigned int _max, unsigned int _min);
    void recieveCard(){};
    void setName(){};
    unsigned int getMoney() { return m_money; }
};

player::player(unsigned int _money, int _cardNum)
{
  m_money = _money;
  m_currentHandNum = _cardNum;
}

boolean player::placeBet(unsigned int _max, unsigned int _min)
{
   boolean quit = false;
   button but;
   
   //need to find a better way of not hardcoding the pin number.
   while(!quit) 
   {
     boolean exit = false;
     boolean confirm = false;
     unsigned int bet = _min;
     int x;
     
     lcd.clear();
     
     lcd.print("Place bet:");
     
     //fixes it from selecting autimatically needs better fix.
     delay(1000);
     
     while(!exit)
     { 
      x= analogRead(0); 
      lcd.setCursor(0,1);
      
      if      (but.right(x) && bet <= (_max-10) && bet < (m_money-10))  { bet+=10;    }
      else if (but.up(x) && bet < _max && bet < m_money)                { bet++;      } 
      else if (but.down(x) && bet > _min && bet < m_money)              { bet--;      }
      else if (but.left(x) && bet >= (_max+10) && bet < (m_money+10))   { bet-=10;    } 
      else if (but.select(x))                                           { exit = true;}
      
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
       x = analogRead(0);
       
       lcd.setCursor(0,1);
       lcd.print("yes:");
       
       lcd.setCursor(7,1);
       lcd.print("no:");
       
       if(but.right(x))        
       {
         lcd.setCursor(5,1); 
         lcd.print(" ");
         lcd.setCursor(11,1); 
         lcd.print("X");
         if(check != 2) {check = 2;}
       }
       else if(but.left(x))    
       {
         lcd.setCursor(5,1); 
         lcd.print("X");
         lcd.setCursor(11,1); 
         lcd.print(" ");
         if(check != 1) {check = 1;}
       }
       else if(but.select(x) && check==1)  
       {
         confirm = true; 
         quit = true;
       }
       else if(but.select(x) && check==2)  
       {
         break;
       }       
     }
     m_money = m_money - bet;
  }
}

void setup() 
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  player test(100, 2);
  
  
}

void loop() 
{
  player test(100, 2);
  
  lcd.clear();
  lcd.print(String(test.getMoney()));
  
  delay(2000);
  
  test.placeBet(200, 10);
  
  lcd.clear();
  lcd.print(String(test.getMoney()));
  
  delay(5000);
 
  
  
  
  /*
  int x;
  x = analogRead (0);
  lcd.setCursor(10,1);
  
  if (x < 60)        {lcd.print("Right ");  }
  else if (x < 200)  {lcd.print ("Up    "); }
  else if (x < 400)  {lcd.print ("Down  "); }
  else if (x < 600)  {lcd.print ("Left  "); }
  else if (x < 800)  {lcd.print ("Select"); }
  */
}
