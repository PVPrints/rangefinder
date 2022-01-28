#ifndef _SCREEN_H
#define _SCREEN_H

#include <Arduino.h>

enum ScreenState { SCREEN_ON, SCREEN_OFF };

class Screen {
  public:
    Screen(byte pin);
    ScreenState tick(boolean mastLowered);

  private:
    ScreenState _state;
    byte _pin;
    ScreenState whenOff(boolean mastLowered);
    ScreenState whenOn(boolean mastLowered);
};

#endif // _SCREEN_H
