MCU=atmega328p
F_CPU=16000000UL

led: led.o spi.o uart.o
	avr-gcc -mmcu=$(MCU) -o led led.o spi.o uart.o

led.o: led.c led.h
	avr-gcc -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -c -o led.o led.c

spi.o: spi.c spi.h
	avr-gcc -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -c -o spi.o spi.c

uart.o: uart.c uart.h
	avr-gcc -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -c -o uart.o uart.c

clean:
	rm *.o led spi
