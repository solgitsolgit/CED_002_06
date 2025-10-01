#include <EEPROM.h> 
int data = 0;
int addr = 0;

void setup() {
  data = 202517066 % 256;
  addr = 2025 % 1024;

  EEPROM.write(addr, data);
}

void loop() {
}

// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066
