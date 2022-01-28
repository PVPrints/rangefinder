#include "Mast.h"

Mast::Mast(
  byte pin,
  int raisedAngle,
  int loweredAngle,
  unsigned long timeout
) {
  _pin = pin;
  _raisedAngle = raisedAngle;
  _loweredAngle = loweredAngle;
  _timeout = timeout;
  _state = MAST_RAISED;
  _moving = true;
}

void Mast::setup()
{
  _servo.attach(_pin);
}

MastState Mast::tick(boolean shouldToggle)
{
  switch (_state) {
    case MAST_RAISED:
      return whenRaised(shouldToggle);
      break;
    case MAST_LOWERED:
      return whenLowered(shouldToggle);
      break;
  }
}

MastState Mast::whenRaised(boolean shouldToggle)
{
  if (shouldToggle) {
    _state = MAST_LOWERED;
    _moving = true;
    _raiseAfter = millis() + _timeout;
    return _state;
  }

  if (_moving) {
    _servo.write(_raisedAngle);
    _moving = false;
  }

  return _state;
}

MastState Mast::whenLowered(boolean shouldToggle)
{
  if (millis() > _raiseAfter) {
    shouldToggle = true;
  }
  
  if (shouldToggle) {
    _state = MAST_RAISED;
    _moving = true;
    return _state;
  }

  if (_moving) {
    _servo.write(_loweredAngle);
    _moving = false;
  }

  return _state;
}
