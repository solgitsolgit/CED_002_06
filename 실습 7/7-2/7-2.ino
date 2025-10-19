// 라이브러리와 변수 설정
#include <SoftwareSerial.h>
static int counter = 0;
SoftwareSerial bt_serial(2,3);

void setup() {
  bt_serial.begin(9600); // Serial baud rate 9600
}

// PuTTY 화면 출력 설정
void loop() {
  bt_serial.print("Tick #");
  bt_serial.print(counter++, DEC); // print counter and increment 1
  bt_serial.print("\n");
  delay(1000); // delay 1 sec
}

// CED 002, group 06, 2020-14247 ShinYee Kang
// CED 002, group 06, 2023-14669 TaeHyun Lim
// CED 002, group 06, 2025-17066 JungHwan Kim