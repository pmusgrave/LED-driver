#!/bin/bash

avr-objcopy -O ihex -R .eeprom LEDStuff LEDStuff.hex
avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:LEDStuff.hex
