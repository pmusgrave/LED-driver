MCU=atmega328p
F_CPU=16000000UL

LEDStuff: LEDStuff.o spitest.o uart.o
	avr-gcc -mmcu=$(MCU) -o LEDStuff LEDStuff.o spitest.o uart.o

LEDStuff.o: LEDStuff.c LEDStuff.h
	avr-gcc -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -c -o LEDStuff.o LEDStuff.c

spitest.o: spitest.c spitest.h
	avr-gcc -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -c -o spitest.o spitest.c

uart.o: uart.c uart.h
	avr-gcc -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -c -o uart.o uart.c

clean:
	rm *.o LEDStuff spitest
