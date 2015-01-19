class input
{
  private:

    //pin to read from
    int m_pin;

    // value read from pin
    int m_value;

  public:

  input(int _pin);
  ~input();

  bool right();
  bool left();
  bool up();
  bool down();
  bool select();

  bool menuYesNo(int _line);


  void updateValue();

};

input::input(int _pin)
{
    m_pin = _pin;
}


bool input::right()
{

    if(m_value <= 60 )  {return true;}
    return false;
}

bool input::left()
  {
    if(m_value <= 600 && m_value >= 401)  {return true;}
    return false;
}

bool input::up()
  {
    if(m_value <= 200 && m_value >= 61 )  {return true;}
    return false;
}

bool input::down()
  {
    if(m_value <= 400 && m_value >= 201)  {return true;}
    return false;
}

bool input::select()
  {
    if(m_value <= 800 && m_value >= 601)  {return true;}
    return false;
}

void input::updateValue()
{
    m_value = analogRead(m_pin);
}

bool input::menuYesNo(int _line)
{
    int check = 0;

    while(true)
    {
      this->updateValue();

      lcd.setCursor(0,_line);
      lcd.print("yes:");

      lcd.setCursor(7,_line);
      lcd.print("no:");

      if(this->right())
      {
        lcd.setCursor(5,_line);
        lcd.print(" ");
        lcd.setCursor(11,_line);
        lcd.print("X");
        if(check != 2) {check = 2;}
      }
      else if(this->left())
      {
        lcd.setCursor(5,_line);
        lcd.print("X");
        lcd.setCursor(11,_line);
        lcd.print(" ");
        if(check != 1) {check = 1;}
      }
      else if(this->select() && check==1)
      {
        return true;
      }
      else if(this->select() && check==2)
      {
        return false;
      }
    }

}
