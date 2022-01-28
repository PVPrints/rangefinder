#include "Activator.h"
#include "Mast.h"
#include "Blinkenlights.h"
#include "Screen.h"

const byte ACTIVATOR_SWITCH_PIN = 2;
const byte BLINKEN_TOP_PIN = 3;
const byte BLINKEN_BOTTOM_PIN = 4;
const byte SCREEN_PIN = 5;
const byte MAST_SERVO_PIN = 9;

const int MAST_RAISED_ANGLE = 100;
const int MAST_LOWERED_ANGLE = 0;

const unsigned long ACTIVATOR_TIMEOUT = 500;
const unsigned long MAST_TIMEOUT = 15000;
const unsigned long BLINKEN_INTERVAL = 250;

Activator activator(
  ACTIVATOR_SWITCH_PIN,
  ACTIVATOR_TIMEOUT
);
Mast mast(
  MAST_SERVO_PIN,
  MAST_RAISED_ANGLE,
  MAST_LOWERED_ANGLE,
  MAST_TIMEOUT
);
Blinkenlights blinkenlights(
  BLINKEN_TOP_PIN,
  BLINKEN_BOTTOM_PIN,
  BLINKEN_INTERVAL
);
Screen screen(SCREEN_PIN);

ActivatorState aState;
MastState mState;
BlinkenState bState;
ScreenState sState;
boolean shouldToggle;
boolean mastLowered;

void setup()
{
  mast.setup();
}

void loop()
{
  aState = activator.tick();
  if (aState == ACTIVATOR_FIRING) {
    shouldToggle = true;
  } else {
    shouldToggle = false;
  }

  mState = mast.tick(shouldToggle);
  if (mState == MAST_LOWERED) {
    mastLowered = true;
  } else {
    mastLowered = false;
  }
  
  bState = blinkenlights.tick(mastLowered);
  sState = screen.tick(mastLowered);
}