MCU=atmega328p
F_CPU=16000000UL

LEDStuff: LEDStuff.o spitest.o
	avr-gcc -mmcu=$(MCU) -o LEDStuff LEDStuff.o spitest.o

LEDStuff.o: LEDStuff.c LEDStuff.h
	avr-gcc -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -c -o LEDStuff.o LEDStuff.c

spitest.o: spitest.c spitest.h
	avr-gcc -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -c -o spitest.o spitest.c

clean:
	rm *.o LEDStuff spitest
