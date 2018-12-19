#include <stdio.h>
#include <unistd.h>
#include <bcm2835.h>

int main(void){
  printf("Initializing SPI configuration...\n");
  bcm2835_init();

  if(bcm2835_spi_begin()){
    printf("SPI init successful\n");

    uint8_t SPI_read_buffer;
    uint8_t dummy_data = 0;

    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);

    // configure SPI rate
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_32768);

    int i = 0;
    while(1){
      // printf("SPI master device sent: %d\tSPI slave device sent: %d\n", i, SPI_read_buffer);
      SPI_read_buffer = bcm2835_spi_transfer(82);
      SPI_read_buffer = bcm2835_spi_transfer(i%255);

      SPI_read_buffer = bcm2835_spi_transfer(71);
      SPI_read_buffer = bcm2835_spi_transfer(i%255);

      SPI_read_buffer = bcm2835_spi_transfer(66);
      SPI_read_buffer = bcm2835_spi_transfer(i%255);      

      i++;
    }

    bcm2835_spi_end();
  }

  return 0;
}
