#include <EEPROM.h>
int data[] = {2, 0, 2, 5, 1, 7, 0, 6, 6};
int addr[9];

void setup() {
  Serial.begin(9600);

  for(int i=0; i<9; i++){
    addr[i] = i;
    EEPROM.write(addr[i], data[i]);
  }
}

void loop() {
  for(int j=0; j<9; j++){
    Serial.print("address is : ");
    Serial.println(addr[j]);
    data[j] = EEPROM.read(addr[j]);
    Serial.print("data is : ");
    Serial.println(data[j]);
    delay(1000);
  }
}

// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066