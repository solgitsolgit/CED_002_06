#include <SoftwareSerial.h>

SoftwareSerial bt_serial(2, 3); // open bluetooth serial with port 2, 3
byte buffer[512]; // 문자열을 저장할 buffer 변수 설정
int buffer_index;

void setup() {
  bt_serial.begin(9600); // serial baud rate 9600
  buffer_index = 0;
}

void loop() {
  if (bt_serial.available() > 0) {

    // Rx part - data를 buffer에 저장
    byte data = (byte) bt_serial.read();
    buffer[buffer_index++] = data;

    if (data == '\n') { // represents the end of the string
      // Tx part - buffer의 data를 다시 전송
      bt_serial.print("REPLY: ");
      buffer[buffer_index] = '\0';
      bt_serial.write(buffer, buffer_index);
      buffer_index = 0;
    }
  }
}

// CED 002, group 06, 2020-14247 ShinYee Kang
// CED 002, group 06, 2023-14669 TaeHyun Lim
// CED 002, group 06, 2025-17066 JungHwan Kim