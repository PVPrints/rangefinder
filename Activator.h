#ifndef _ACTIVATOR_H
#define _ACTIVATOR_H

#include <Arduino.h>

enum ActivatorState { ACTIVATOR_READY, ACTIVATOR_FIRING, ACTIVATOR_MUTED };

class Activator
{
  public:
    Activator(byte pin, unsigned long timeout);
    ActivatorState tick();
    
  private:
    ActivatorState _state;
    unsigned long _muteUntil;
    byte _pin;
    unsigned long _timeout;
    ActivatorState whenReady();
    ActivatorState whenFiring();
    ActivatorState whenMuted();
};

#endif // _ACTIVATOR_H
