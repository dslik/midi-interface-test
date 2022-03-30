## Overview

This is a simple program for a Raspberry Pi Pico that tests a MIDI interface board.

The following subsystems are tested:

* WS2812 LEDs
* MIDI Input
* MIDI Output

## Build Instructions

1. Set up the Pi Pico example programs and build system
2. Successfully build and deploy the "blink" example via SWD
3. Connect UART0 to view debugging output
4. Check out this project
5. Create a "build" directory
6. Inside the build directory, run "cmake ../"
7. Make and install the built "miditest.elf" executable.

## Test Instructions

The MIDI input and output should be connected to a MIDI instrument, or a computer interface.

The Raspberry Pi Pico used to test the interface board should be connected as documented in the source code.

When run, the following output will be displayed:

![image](https://user-images.githubusercontent.com/5757591/160741134-70434a3c-339c-438c-aab2-1c85b3195ffd.png)

MIDI output can be monitored using [Midi View](https://hautetechnique.com/midi/midiview/) or a similar MIDI monitoring program.

The following test output will be sent:

![image](https://user-images.githubusercontent.com/5757591/160741346-7b568671-54d6-48c8-a6da-0cdb29b9b909.png)
