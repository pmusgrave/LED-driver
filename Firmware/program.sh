#!/bin/bash

avr-objcopy -O ihex -R .eeprom led led.hex
avrdude -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 19200 -U flash:w:led.hex
