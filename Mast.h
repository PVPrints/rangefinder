#ifndef _MAST_H
#define _MAST_H

#include <Arduino.h>
#include <Servo.h>

enum MastState { MAST_RAISED, MAST_LOWERED };

class Mast
{
  public:
    Mast(
      byte pin,
      int raisedAngle,
      int loweredAngle,
      unsigned long timeout
    );
    void setup();
    MastState tick(boolean shouldToggle);

  private:
    MastState _state;
    boolean _moving;
    unsigned long _raiseAfter;
    Servo _servo;
    byte _pin;
    int _raisedAngle;
    int _loweredAngle;
    unsigned long _timeout;
    MastState whenRaised(boolean shouldToggle);
    MastState whenLowered(boolean shouldToggle);
};

#endif // _MAST_H
