#include "Blinkenlights.h"

Blinkenlights::Blinkenlights(
  byte top_pin,
  byte bottom_pin,
  byte flashlight_pin,
  unsigned long interval
) {
  _top_pin = top_pin;
  _bottom_pin = bottom_pin;
  _flashlight_pin = flashlight_pin;
  _interval = interval;
  _state = BLINKEN_OFF;
  pinMode(_top_pin, OUTPUT);
  pinMode(_bottom_pin, OUTPUT);
}

BlinkenState Blinkenlights::tick(boolean mastLowered)
{
  switch (_state) {
    case BLINKEN_OFF:
      return whenOff(mastLowered);
      break;
    case BLINKEN_BLINK_OFF:
      return whenBlinkOff(mastLowered);
      break;
    case BLINKEN_BLINK_ON:
      return whenBlinkOn(mastLowered);
      break;
    case BLINKEN_FLASHLIGHT:
      return whenFlashlight(mastLowered);
      break;
  }
}

BlinkenState Blinkenlights::whenOff(boolean mastLowered)
{
  digitalWrite(_top_pin, LOW);
  digitalWrite(_bottom_pin, LOW);
  digitalWrite(_flashlight_pin, LOW);
  
  if (mastLowered) {
    _blinkAfter = millis() + _interval;
    _state = BLINKEN_BLINK_OFF;
  }

  return _state;
}

BlinkenState Blinkenlights::whenBlinkOff(boolean mastLowered)
{
  digitalWrite(_top_pin, LOW);
  digitalWrite(_bottom_pin, HIGH);
  digitalWrite(_flashlight_pin, LOW);

  unsigned long now = millis();
  if (now > _blinkAfter) {
    _blinkAfter = now + _interval;
    _state = BLINKEN_BLINK_ON;
  }

  if (!mastLowered) {
    _state = BLINKEN_OFF;
  }

  return _state;
}

BlinkenState Blinkenlights::whenBlinkOn(boolean mastLowered)
{
  digitalWrite(_top_pin, HIGH);
  digitalWrite(_bottom_pin, HIGH);
  digitalWrite(_flashlight_pin, LOW);

  unsigned long now = millis();
  if (now > _blinkAfter) {
    _blinkAfter = now + _interval;
    _state = BLINKEN_BLINK_OFF;
  }

  if (!mastLowered) {
    _state = BLINKEN_OFF;
  }

  return _state;
}

BlinkenState Blinkenlights::whenFlashlight(boolean mastLowered)
{
  digitalWrite(_top_pin, LOW);
  digitalWrite(_bottom_pin, LOW);
  digitalWrite(_flashlight_pin, HIGH);

  if (!mastLowered) {
    _state = BLINKEN_OFF;
  }

  return _state;
}
