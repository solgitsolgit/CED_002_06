// ==== Experiment 4: LDR -> LED (A0, D2) ====
const int LED_PIN = 5;
const int LED_ON_THRESHOLD = 50; // 주변 밝기에 맞게 조정

void setup() {
  Serial.begin(9600); // Begin serial communication
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int sensed_light = analogRead(A0); // 0~1023

  if (sensed_light > LED_ON_THRESHOLD)
    digitalWrite(LED_PIN, HIGH);
  else
    digitalWrite(LED_PIN, LOW);

  Serial.println(sensed_light);
  delay(500);
}
// CED 002, group 06, 2020-14247 강신의
// CED 002, group 06, 2023-14669 임태현
// CED 002, group 06, 2025-17066 김정환