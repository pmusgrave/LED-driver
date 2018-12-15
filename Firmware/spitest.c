/*
 * spitest.c
 *
 * Created: 12/14/2018
 * Author : Paul Musgrave
 */

#define F_CPU 16000000UL

#include <avr/io.h>

void SPI_SlaveInit(void);
int SPI_SlaveReceive(void);
void SerialInit(void);
void SerialWrite(int);
void SetLED(void);
void ClearLED(void);

// #define LED_PIN 5
#define LED_PIN 3
#define SPI_DDR DDRB
#define SPI_SS DDB2
#define SPI_MOSI DDB3
#define SPI_MISO DDB4
#define SPI_SCK DDB5

int main(void){
	// -------- Inits --------- //
  DDRD |= 0xff;
  SerialInit();
	SPI_SlaveInit();

	int SpiBuffer = 0;
  unsigned int i = 0;

	// ------ Event loop ------ //
	while (1) {
    SPDR = i;
		SpiBuffer = SPI_SlaveReceive();
    // SerialWrite(SpiBuffer);
    if (SpiBuffer%2 == 0){
      SetLED();
    }
    else{
      ClearLED();
    }
    i++;
	}
	return 0;
}


// from datasheet example
void SPI_SlaveInit(void)
{
	PRR &= ~(1 << PRSPI);
	// Set MISO output, all others input
	SPI_DDR = (1<<SPI_MISO);
	// Enable SPI
	SPCR = (1<<SPE);
}

// from datasheet example
int SPI_SlaveReceive(void){
	/*
	Bit 7 � SPIF0: SPI Interrupt Flag
	When a serial transfer is complete, the SPIF Flag is set. An interrupt is generated if SPIE in SPCR is set
	and global interrupts are enabled. If SS is an input and is driven low when the SPI is in Master mode, this
	will also set the SPIF Flag. SPIF is cleared by hardware when executing the corresponding interrupt
	handling vector. Alternatively, the SPIF bit is cleared by first reading the SPI Status Register with SPIF
	set, then accessing the SPI Data Register (SPDR).
	*/
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)))
	;
	/* Return Data Register */
	return SPDR;
}

void SerialInit(void){
  // based on datasheet example configuration
  /*Set baud rate */
  UBRR0H = (unsigned char)(9600>>8);
  //UBRR0L = (unsigned char)9600;
  /*Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  /* Set frame format: 8data, 1stop bit */
  UCSR0C = (3<<UCSZ00);
}

void SerialWrite(int data){
  /* Wait for empty transmit buffer */
  while ( !( UCSR0A & (1<<UDRE0)) )
  ;
  /* Put data into buffer, sends the data */
  UDR0 = data;
}

void SetLED(void){
	PORTD |= (1<<LED_PIN);
}


void ClearLED(void){
	PORTD &= ~(1<<LED_PIN);
}
