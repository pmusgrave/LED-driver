MCU=atmega328p
F_CPU=16000000UL

LEDStuff: LEDStuff.o
	avr-gcc -mmcu=$(MCU) LEDStuff.o -o LEDStuff

LEDStuff.o: LEDStuff.c LEDStuff.h
	avr-gcc -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -c -o LEDStuff.o LEDStuff.c

spitest: spitest.o
	avr-gcc -mmcu=$(MCU) spitest.o -o spitest

spitest.o: spitest.c
	avr-gcc -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -c -o spitest.o spitest.c

clean:
	rm *.o LEDStuff spitest
