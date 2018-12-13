#!/bin/bash

#avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o LEDStuff.o LEDStuff.c
#avr-gcc -mmcu=atmega328p LEDStuff.o -o LEDStuff
avr-objcopy -O ihex -R .eeprom LEDStuff LEDStuff.hex
avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:LEDStuff.hex
