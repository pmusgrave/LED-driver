// credit to Elliot Williams
// some code adapted from Make: AVR Programming
#define BAUD 9600

void initUART(void);
void transmitByte(uint8_t data);
uint8_t receiveByte(void);
void printString(const char myString[]);
