#include "Activator.h"

Activator::Activator(byte pin, unsigned long timeout)
{
  _pin = pin;
  _timeout = timeout;
  _state = ACTIVATOR_READY;
  pinMode(_pin, INPUT_PULLUP);
}

ActivatorState Activator::tick()
{
  switch (_state) {
    case ACTIVATOR_READY:
      return whenReady();
      break;
    case ACTIVATOR_FIRING:
      return whenFiring();
      break;
    case ACTIVATOR_MUTED:
      return whenMuted();
      break;
  }
}

ActivatorState Activator::whenReady()
{
  /* LOW == pressed, HIGH == not pressed; thanks, pullup! */
  if (digitalRead(_pin) == LOW) {
    _state = ACTIVATOR_FIRING;
  }
  return _state;
}

ActivatorState Activator::whenFiring()
{
  _muteUntil = millis() + _timeout;
  _state = ACTIVATOR_MUTED;
  return _state;
}

ActivatorState Activator::whenMuted()
{
  if (millis() >= _muteUntil) {
    _state = ACTIVATOR_READY;
  }
  return _state;
}
