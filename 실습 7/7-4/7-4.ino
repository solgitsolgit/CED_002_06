#include <SoftwareSerial.h>

SoftwareSerial bt_serial(2, 3); // open bluetooth serial with port 2, 3
byte buffer[512];
int buffer_index;

void setup() {
  // put your setup code here, to run once:
  bt_serial.begin(9600); // serial baud rate 9600
  buffer_index = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (bt_serial.available() > 0) {
    // Rx part
    byte data = (byte) bt_serial.read();
    
    // 버퍼가 오버플로우되지 않도록 체크하는 코드를 추가하는 것이 좋습니다.
    if (buffer_index < 512) {
      buffer[buffer_index++] = data;
    }
    
    if (data == '\n') { // represents the end of the string
      // Tx part
      bt_serial.print("REPLY: ");
      
      // 문자열 끝을 나타내는 널 문자('\0')를 추가합니다.
      // (buffer_index는 현재 다음 데이터가 저장될 위치를 가리키므로, 받은 문자 수와 같습니다.)
      buffer[buffer_index] = '\0';
      
      // 버퍼에 저장된 데이터를 수신된 문자 수(buffer_index)만큼 전송합니다.
      bt_serial.write(buffer, buffer_index);
      
      buffer_index = 0;
    }
  }
}