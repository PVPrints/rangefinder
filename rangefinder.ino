#include <Servo.h>

Servo rangefinder;

const int BUTTON_PIN = 2;
const int BLINKER_PIN_0 = 3;
const int BLINKER_PIN_1 = 4;
const int SCREEN_PIN = 5;
const int BUTTON_READY_PIN = 6;
const int RF_PIN = 9;
const int RF_UP_ANGLE = 100;
const int RF_DOWN_ANGLE = 0;

const int BLINKER_INTERVAL = 250;
const int BUTTON_TIMEOUT = 1000;
const int RF_TIMEOUT = 15000;

int val = 0;
int buttonState = 0;
int rfAngle = 0;
int blinker = 0;

unsigned long then = 0;
unsigned long now = 0;
unsigned long lastPress = 0;
unsigned long lastBlinker = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BLINKER_PIN_0, OUTPUT);
  pinMode(BLINKER_PIN_1, OUTPUT);
  pinMode(SCREEN_PIN, OUTPUT);
  pinMode(BUTTON_READY_PIN, OUTPUT);
  rangefinder.attach(RF_PIN);
  delay(1);
  raiseRF();
}

void loop()
{
  swapThenNow();

  if (buttonReady()) {
    Serial.println("Button ready");
    digitalWrite(BUTTON_READY_PIN, HIGH);
  } else {
    Serial.println("Button not ready");
    digitalWrite(BUTTON_READY_PIN, LOW);
  }
  
  buttonState = readButton();
  if (buttonState == LOW) {
    Serial.println("Toggling rangefinder");
    toggleRF();
  }
  swapBlinkers();
}

int readButton()
{
  if (buttonReady()) {
    int state = digitalRead(BUTTON_PIN);
    if (state == LOW) {
      Serial.println("Button pressed");
      lastPress = now;
      return LOW;
    }
  } else {
    return HIGH;
  }
}

int buttonReady()
{
  return now - lastPress >= BUTTON_TIMEOUT;
}

int blinkerSwapReady()
{
  return now - lastBlinker >= BLINKER_INTERVAL;
}

void swapThenNow()
{
  then = now;
  now = millis();
  if (then > now) {
    // If this code ever runs, then someone *really* needs to take
    // a break from wearing the Boba suit.  Like dank farrik, dude,
    // it's been 50 kriffing days, please recharge the battery and
    // take a shower for Force's sake.
    then = 0;
  }
}

void toggleRF()
{
  if (rfAngle == RF_DOWN_ANGLE) {
    Serial.println("Rangefinder going up");
    raiseRF();
  } else {
    Serial.println("Rangefinder going down");
    lowerRF();
  }
}

void swapBlinkers()
{
  if (rfAngle == RF_DOWN_ANGLE) {
    if (blinkerSwapReady()) {
      lastBlinker = now;
      if (blinker) {
        blinker = 0;
        Serial.println("Blinkers: HIGH, LOW");
        setBlinkers(HIGH, LOW);
      } else {
        blinker = 1;
        Serial.println("Blinkers: LOW, HIGH");
        setBlinkers(LOW, HIGH);
      }
    } else {
      setBlinkers(LOW, LOW);
    }
  }
}

void setBlinkers(int b0, int b1)
{
  digitalWrite(BLINKER_PIN_0, b0);
  digitalWrite(BLINKER_PIN_1, b1);
}

void setRF(int angle, int light)
{
  rangefinder.write(angle);
  digitalWrite(SCREEN_PIN, light);
  rfAngle = angle;
}

void raiseRF()
{
  setRF(RF_UP_ANGLE, LOW);
}

void lowerRF()
{
  setRF(RF_DOWN_ANGLE, HIGH);
}
