#include <EEPROM.h>
int data = 0;
int addr = 0;

void setup() {
  data = 202314669 % 256;

  addr = 2023 % 1024;

  EEPROM.write(addr, data);

}

void loop() {
  // put your main code here, to run repeatedly:

}

//group 6 2023-14669