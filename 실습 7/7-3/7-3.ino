#include <SoftwareSerial.h>

SoftwareSerial bt_serial(2, 3); // open bluetooth serial with port 2, 3

void setup() {
  bt_serial.begin(9600); // serial baud rate 9600
  pinMode(13, OUTPUT);
}

void loop() {
  if (bt_serial.available() > 0) {
    byte data = (byte) bt_serial.read();
    if (data == 'h') {
      digitalWrite(13, HIGH); // h 입력시 LED 켜기
    }
    if (data == 'l') {
      digitalWrite(13, LOW); // l 입력시 LED 끄기
    }
  }
}

// CED 002, group 06, 2020-14247 ShinYee Kang
// CED 002, group 06, 2023-14669 TaeHyun Lim
// CED 002, group 06, 2025-17066 JungHwan Kim