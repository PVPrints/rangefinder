#include "Activator.h"

Activator::Activator(byte aim_pin, byte flashlight_pin, unsigned long timeout)
{
  _aim_pin = aim_pin;
  _flashlight_pin = flashlight_pin;
  _timeout = timeout;
  _state = ACTIVATOR_READY;
  pinMode(_aim_pin, INPUT_PULLUP);
  pinMode(_flashlight_pin, INPUT_PULLUP);
}

ActivatorState Activator::tick()
{
  switch (_state) {
    case ACTIVATOR_READY:
      return whenReady();
      break;
    case ACTIVATOR_AIMING:
      return whenAiming();
      break;
    case ACTIVATOR_FLASHLIGHT:
      return whenFlashlight();
      break;
    case ACTIVATOR_MUTED:
      return whenMuted();
      break;
  }
}

ActivatorState Activator::whenReady()
{
  /* LOW == pressed, HIGH == not pressed; thanks, pullup! */
  if (digitalRead(_aim_pin) == LOW) {
    _state = ACTIVATOR_AIMING;
  }
  if (digitalRead(_flashlight_pin) == LOW) {
    _state = ACTIVATOR_FLASHLIGHT;
  }
  return _state;
}

ActivatorState Activator::whenAiming()
{
  _muteUntil = millis() + _timeout;
  _state = ACTIVATOR_MUTED;
  return _state;
}

ActivatorState Activator::whenFlashlight()
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
