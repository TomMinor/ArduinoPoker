//MAKE_TYPE_INFO( char )
/// @brief input class
/// @author George Madges
/// @version 1.0
/// @date 21/01/2015

#ifndef INPUT_H
#define INPUT_H

#include "Arduino.h"
#include <LiquidCrystal.h>
#include "pokerDisplay.h"


class input
{
  private:

  /// @brief pin being used from the arduino.
  int m_pin;

  /// @brief value obtained from the pin.
  int m_value;
  
  
  public:

  /// @brief ctor
  input();

  /// @brief dtor.
  ~input();
  
  /// @brief setPin
  /// @param [in] pin to analogRead from.
  void setPin(int _pin);

  /// @brief right input
  /// @param [out] returns bool of true if right button is pressed.
  bool right();

  /// @brief left input
  /// @param [out] returns bool of true if left button is pressed.
  bool left();

  /// @brief up input
  /// @param [out] returns bool of true if up button is pressed.
  bool up();

  /// @brief down input
  /// @param [out] returns bool of true if down button is pressed.
  bool down();

  /// @brief select input
  /// @param [out] returns bool of true if select button is pressed.
  bool select();

  /// @brief function to print yes, no options and returns their option.
  /// @param [in] _line, which line to print to.
  /// @return [out] return bool, true or false = yes or no.
  bool menuYesNo(int _line);

  /// @brief updates the m_value using analogRead.
  void updateValue();

};


#endif
