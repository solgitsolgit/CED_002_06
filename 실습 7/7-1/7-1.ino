void setup () {
  Serial.begin(9600); // serial baud rate 9600
  pinMode(13, OUTPUT); // pin mode
}

void loop() {
  if (Serial.peek() != -1) {
    byte data = (byte) Serial.read();
    if (data == 'h') {
      digitalWrite(13, HIGH); // set the LED high
    }
    if (data == 'l') {
      digitalWrite(13, LOW); // set the LED low
    }
  }
}

// CED 002, group 06, 2020-14247 강신의
// CED 002, group 06, 2023-14669 임태현
// CED 002, group 06, 2025-17066 김정환