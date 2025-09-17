const int LightPin = A0; // 광센서 핀 설정
const int LedPin = 13;
const int Threshold = 500; // 광센서 임계값 설정

void setup() {
  Serial.begin(9600);
  pinMode(LedPin, OUTPUT);
}

void loop() {
  int lightValue = analogRead(LightPin); // 광센서 Vout Value

  Serial.print("Vout Value: ");
  Serial.println(lightValue); // 시리얼 프린터에 출력

  if (lightValue > Threshold) {
    digitalWrite(LedPin, HIGH); // 값이 임계값보다 높으면 Led 켜기
  }
  else {
    digitalWrite(LedPin, LOW); // 값이 임계값보다 낮으면 Led 끄기
  }

  delay(100);
}

// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066