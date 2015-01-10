#include "input.h"


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
