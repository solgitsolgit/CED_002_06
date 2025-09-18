//핀 설정
int lightPin = 10;
int ledPin = 11;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  Serial.println(digitalRead(lightPin));
//빛이 약하면 led 키기
  if (digitalRead(lightPin) == 1) {
    digitalWrite(ledPin, 1);
  }
//빛이 강하면 led 끄기
  else {
    digitalWrite(ledPin, 0);
  }

  delay(10);
}

// CED 002, group 06, 2020-14247 강신의
// CED 002, group 06, 2023-14669 임태현
// CED 002, group 06, 2025-17066 김정환