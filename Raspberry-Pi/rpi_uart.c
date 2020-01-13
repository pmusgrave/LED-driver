#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>

int main(void){
  printf("Initializing serial configuration...\n");
  int fd = -1;
  if( (fd = serialOpen("/dev/serial0", 9600)) >= 0){
    printf("Serial configuration for fd %d complete\n",fd);

    while (1) {
      serialPutchar(fd, 'R');
      delay(400);
      serialPutchar(fd, 'r');
      delay(400);
      serialPutchar(fd, 'G');
      delay(400);
      serialPutchar(fd, 'g');
      delay(400);
      serialPutchar(fd, 'B');
      delay(400);
      serialPutchar(fd, 'b');
      delay(400);
      printf("%c", serialGetchar(fd));
      printf("%c", serialGetchar(fd));
      printf("%c", serialGetchar(fd));
    }
  }
  else {
    printf("%d Error configuring serial port\n", fd);
    // fprintf(stdout, "Error %s\n", strerror(errno));
  }
  
  serialClose(fd);
  
  return 0;
}
