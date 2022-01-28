# rangefinder

## What is it?

It's a collection of Arduino code to drive a servo and LEDs for a helmet-mounted rangefinder on prop/cosplay helmets - namely, those replicating the helmet worn by a certain character played by Temeura Morrison in a certain digitally-streamed science fiction television show.

## How do I use it?

Easiest way would be to clone this repository somewhere (or download/extract the Zip archive), then open `rangefinder.ino` in the Arduino IDE.  From there, you can compile and upload the resulting sketch to an Arduino Nano (or Uno, or anything else compatible with those).

### What pins does it use?

Note that we're actively fiddling with how this thing's supposed to be wired, so the power/ground pins listed here might not reflect what we're shipping in physical units, but the data pins should stay consistent (and they're the important part for this codebase anyway).

* D2: Activator (any momentary switch/button should do)
* D3/4: Blinkenlight LEDs, top/bottom
* D5: Screen LED
* D9: Mast servo PWM
* VIN: Battery V+
* 5V: Mast servo power
* GND1/2: Grounds for everything

### How does it work?

There are four software state machines in use: Activator, Mast, Blinkenlights, and Screen.  These correspond to various hardware components (momentary button/switch, servo, red LEDs, and an LED for the "screen", respectively).

On powerup, Blinkenlights and Screen are turned off, Mast is raised to vertical position, and Activator waits for a signal.

Once Activator receives a signal, Mast lowers to horizontal/forward, Blinkenlights turn on (top light blinks at 4Hz, bottom light remains steady), Screen turns on, and Activator sleeps for half a second (for debouncing / anti-jitter) before waiting for another signal.

Upon Activator receiving another signal or Mast being lowered for 15 seconds (whichever comes first), Mast raises back to vertical, Blinkenlights and Screen turn off.  Rinse and repeat.

## How do I hack on it?

We've included the Wokwi project/diagram files in the repo, so you should be able to upload the contents of this repo right into it and get up and running right away.  You can also obviously use the Arduino IDE (or anything else that can edit and compile Arduino's not-quite-C++).  Pull requests are welcome :)

## Any known issues with it?

The timing code uses the standard Arduino approach of an `unsigned long` representing the number of milliseconds since powerup.  This will overflow after a few weeks and probably cause some weirdness.  If you actually manage to run this thing for the 50 or so days straight that would be necessary for this to be an issue, then congrats: you're a much bigger Star Wars nerd than any of us here at PVPrints, but dank farrik, dude, please turn off the helmet circuitry and go take a kriffing shower or something for Force's sake, lol

## Am I allowed to use it?

License TBD
