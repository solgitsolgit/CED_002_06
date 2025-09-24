void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue1 = digitalRead(A0); // Line tracer의 A0의 값을 read
  Serial.println(sensorValue1); // 값 출력 (검은색 트랙 : 1, 흰색 배경 : 0)
  delay(100);
}

// CED 002, group 06, 2020-14247, 강신의
// CED 002, group 06, 2023-14669, 임태현
// CED 002, group 06, 2025-17066, 김정환
