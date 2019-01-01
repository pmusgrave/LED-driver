#include <stdio.h>
#include <unistd.h>
#include <bcm2835.h>

#define ASCII_R 82
#define ASCII_G 71
#define ASCII_B 66

int main(void){
  printf("Initializing SPI configuration...\n");
  bcm2835_init();

  if(bcm2835_spi_begin()){
    printf("SPI init successful\n");

    uint8_t SPI_read_buffer;
    uint8_t dummy_data = 0;

    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);

    // configure SPI rate
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536);

    int i = 0;
    while(1){
      // printf("SPI master device sent: %d\tSPI slave device sent: %d\n", i, SPI_read_buffer);

      i++;
      SPI_read_buffer = bcm2835_spi_transfer(ASCII_R);
      SPI_read_buffer = bcm2835_spi_transfer(i);

      
      SPI_read_buffer = bcm2835_spi_transfer(ASCII_G);
      SPI_read_buffer = bcm2835_spi_transfer(i);

      SPI_read_buffer = bcm2835_spi_transfer(ASCII_B);
      SPI_read_buffer = bcm2835_spi_transfer(i);      
     
    }

    bcm2835_spi_end();
  }

  return 0;
}
