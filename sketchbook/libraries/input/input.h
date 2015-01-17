#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#include <arduino.h>

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

  bool right() ;
  bool left();
  bool up();
  bool down();
  bool select();

  bool menuYesNo(int _line);

  void updateValue();

};


#endif
