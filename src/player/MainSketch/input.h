template <typename T_ty> struct TypeInfo { static const char * name; };
template <typename T_ty> const char * TypeInfo<T_ty>::name = "unknown";

#define TYPE_NAME(var) TypeInfo< typeof(var) >::name

#define MAKE_TYPE_INFO(type)  template <> const char * TypeInfo<type>::name = #type;

//MAKE_TYPE_INFO( char )

#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "pokerDisplay.h"


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
