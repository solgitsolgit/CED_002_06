#include <EEPROM.h>
int data;
int addr;

void setup() {
  Serial.begin(9600);
  addr = 2023 % 1024;
}

void loop() {
  Serial.print("address is : ");
  Serial.println(addr);
  data = EEPROM.read(addr);
  Serial.print("data is : ");
  Serial.println(data);
  delay(2000);
}

//group 6 2023-14669