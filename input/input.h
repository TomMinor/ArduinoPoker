#ifndef INPUT_H__
#define INPUT_H__

#define ARDUINO_H__
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#include <arduino.h>

class input
{

public:

    input(int _pin);
    ~input();

    bool buttonUP();
    bool buttonDOWN();
    bool buttonLEFT();
    bool buttonRIGHT();
    bool buttonSELECT();


private:

    int m_x;
    int m_pin;

};

input::input(int _pin)
{
  m_pin = analogRead(_pin);
}

input::~input()
{

}

bool input::buttonUP()
{
  m_x = analogRead(m_pin);
  if(m_x < 200 && m_x > 60) {return true;  }
  else                      {return false; }
}

bool input::buttonDOWN()
{
  m_x = analogRead(m_pin);
  if(m_x < 400 && m_x > 200){return true;  }
  else                      {return false; }
}

bool input::buttonLEFT()
{
  m_x = analogRead(m_pin);
  if(m_x < 600 && m_x > 400){return true;  }
  else                      {return false; }
}

bool input::buttonRIGHT()
{
  m_x = analogRead(m_pin);
  if(m_x < 60) {return true;  }
  else         {return false; }
}

bool input::buttonSELECT()
{
    m_x = analogRead(m_pin);
    if(m_x < 600 && m_x > 400){return true;  }
    else                      {return false; }
}



#endif
