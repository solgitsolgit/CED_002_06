//라인트레이어 센서의 핀 번호 설정
#define leftSensorPin A0
#define centerSensorPin A1
#define rightSensorPin A2

void setup() {
  Serial.begin(9600);
  pinMode(leftSensorPin, INPUT);
  pinMode(centerSensorPin, INPUT);
  pinMode(rightSensorPin, INPUT);
}

void loop() {
// 센서의 값 read (검은색 트랙 : 1, 흰색 배경 : 0)
  int leftSensorValue = digitalRead(leftSensorPin);
  int centerSensorValue = digitalRead(centerSensorPin);
  int rightSensorValue = digitalRead(rightSensorPin);

// 시리얼 모니터에 값 출력
  Serial.print(leftSensorValue);
  Serial.print(centerSensorValue);
  Serial.println(rightSensorValue);

  delay(100);
}

// CED 002, group 06, 2020-14247, 강신의
// CED 002, group 06, 2023-14669, 임태현
// CED 002, group 06, 2025-17066, 김정환
