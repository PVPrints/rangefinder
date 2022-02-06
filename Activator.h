#ifndef _ACTIVATOR_H
#define _ACTIVATOR_H

#include <Arduino.h>

enum ActivatorState {
  ACTIVATOR_READY,
  ACTIVATOR_AIMING,
  ACTIVATOR_FLASHLIGHT,
  ACTIVATOR_MUTED
};

class Activator
{
  public:
    Activator(
      byte aim_pin,
      byte flashlight_pin,
      unsigned long timeout
    );
    ActivatorState tick();
    
  private:
    ActivatorState _state;
    unsigned long _muteUntil;
    byte _aim_pin;
    byte _flashlight_pin;
    unsigned long _timeout;
    ActivatorState whenReady();
    ActivatorState whenAiming();
    ActivatorState whenFlashlight();
    ActivatorState whenMuted();
};

#endif // _ACTIVATOR_H
