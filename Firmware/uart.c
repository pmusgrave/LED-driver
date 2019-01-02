// credit to Elliot Williams
// some code adapted from Make: AVR Programming

#include <avr/io.h>
#include "uart.h"
#include <util/setbaud.h>

void initUART(void) {
  // enable UART TX and RX
  UCSR0B = (1 << TXEN0) | (1 << RXEN0);

  // 8 data bits
  UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

  UBRR0L = UBRRL_VALUE;
  UBRR0H = UBRRH_VALUE;
}

void transmitByte(uint8_t data) {
  while(!(UCSR0A & (1 << UDRE0)))
    ;
  UDR0 = data;
}

uint8_t receiveByte(void) {
  while(!(UCSR0A & (1 << RXC0)))
    ;
  return UDR0;
}

void printString(const char myString[]) {
  uint8_t i = 0;
  while (myString[i]) {
    transmitByte(myString[i]);
    i++;
  }
}
