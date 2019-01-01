#ifndef SPITEST_H
#define SPITEST_H

void SPI_SlaveInit(void);
void SPI_Disable(void);
int SPI_SlaveReceive(void);

#define SPI_DDR DDRB
#define SPI_SS DDB2
#define SPI_MOSI DDB3
#define SPI_MISO DDB4
#define SPI_SCK DDB5

#define SPI_START_RX PD4

#endif
