#ifndef _BLINKENLIGHTS_H
#define _BLINKENLIGHTS_H

#include <Arduino.h>

enum BlinkenState {
  BLINKEN_OFF,
  BLINKEN_BLINK_OFF,
  BLINKEN_BLINK_ON,
  BLINKEN_FLASHLIGHT
};

class Blinkenlights {
  public:
    Blinkenlights(
      byte top_pin,
      byte bottom_pin,
      byte flashlight_pin,
      unsigned long interval
    );
    BlinkenState tick(boolean mastLowered);

  private:
    BlinkenState _state;
    unsigned long _blinkAfter;
    byte _top_pin;
    byte _bottom_pin;
    byte _flashlight_pin;
    unsigned long _interval;
    BlinkenState whenOff(boolean mastLowered);
    BlinkenState whenBlinkOff(boolean mastLowered);
    BlinkenState whenBlinkOn(boolean mastLowered);
    BlinkenState whenFlashlight(boolean mastLowered);
};

#endif // _BLINKENLIGHTS_H
