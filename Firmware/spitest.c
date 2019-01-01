/*
 * spitest.c
 *
 * Created: 12/14/2018
 * Author : Paul Musgrave
 */

#include <avr/io.h>
#include "spitest.h"

// from datasheet example
void SPI_SlaveInit(void)
{
	PRR &= ~(1 << PRSPI);
	// Set MISO output, all others input
	SPI_DDR = (1<<SPI_MISO);
	// Enable SPI
	SPCR = (1<<SPE) | (1<<SPIE);
}

void SPI_Disable(void){
	SPI_DDR = 0xFF;
	SPCR &= ~(1<<SPE) | ~(1<<SPIE);
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
