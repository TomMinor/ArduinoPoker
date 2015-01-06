// include the library code:
#include <LiquidCrystal.h>

// couple things just for testing
#define PlaceBet       1
#define ReceiveCard    2
#define Reset          3
#define SetName        4
#define GetName        5

class player
{
private:
    unsigned int m_money;
    char m_playerName[];
    int m_currentHandNum;

  public:
    player();
    ~player();

    void placeBet();
    void recieveCard();
    void setName();
};

player::player(unsigned int _money, int _cardNum)
{
  m_money = _money;
  m_currentHandNum = _cardNum;
}

player::placeBet()
{
}

player::setName()
{
  lcd.clear();
  lcd.print("Enter Name:")
  int button = 0;
  while()
  {
    button = analogRead(0); 
  }
}



// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() 
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  
  int command;
  
}

void loop() 
{
  
  //command = comms.GetCommand();
  
  switch (command) 
  {
    case PlaceBet:
    {
      //receive more data
      
      player.placeBet();
      break;
    }
    default: 
      // statements
  }
  
  
  
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
