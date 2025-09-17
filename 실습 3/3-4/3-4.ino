//핀 설정
const int ledPin = 13;
const int inputPin = 2;

//핀모드 설정
void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
}

void loop() {
  int value = digitalRead(inputPin);
  //움직임 감지 시 led 키기
  if (value == HIGH) {
    digitalWrite(ledPin, HIGH);
  //그렇지 않은 경우 끄기
  } else {
    digitalWrite(ledPin, LOW);
  }
}

// group 6, 2020-14247 강신의, 2023-14669 임태현, 2025-17066 김정환