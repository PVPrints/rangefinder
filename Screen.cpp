#include "Screen.h"

Screen::Screen(byte pin)
{
  _pin = pin;
  _state = SCREEN_OFF;
  pinMode(_pin, OUTPUT);
}

ScreenState Screen::tick(boolean mastLowered)
{
  switch (_state) {
    case SCREEN_OFF:
      return whenOff(mastLowered);
      break;
    case SCREEN_ON:
      return whenOn(mastLowered);
      break;
  }
}


ScreenState Screen::whenOff(boolean mastLowered)
{
  digitalWrite(_pin, LOW);
  
  if (mastLowered) {
    _state = SCREEN_ON;
  }

  return _state;
}

ScreenState Screen::whenOn(boolean mastLowered)
{
  digitalWrite(_pin, HIGH);

  if (!mastLowered) {
    _state = SCREEN_OFF;
  }

  return _state;
}
