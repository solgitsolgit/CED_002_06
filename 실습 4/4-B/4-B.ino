//핀 설정
#define TRIGGER_PIN 12
#define ECHO_PIN 11
#define redLed 7
#define yellowLed 6
#define greenLed 5


void setup() {
  Serial.begin(9600);

// 핀모드 설정
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(redLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
}

void loop() {
// 초음파 센서 거리 측정
  long duration, cm;
  
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH);
  cm = duration / 29 / 2;

  // 측정된 거리를 시리얼 모니터에 출력
  Serial.print(cm);
  Serial.println(" cm");

  // 거리에 따라 LED 점등
  if (cm <= 5) {
    digitalWrite(greenLed, HIGH);
    digitalWrite(yellowLed, HIGH);
    digitalWrite(redLed, HIGH);
  } 
  
  else if (cm <= 10) {
    digitalWrite(greenLed, HIGH);
    digitalWrite(yellowLed, HIGH);
    digitalWrite(redLed, LOW);
  } 
  
  else if (cm <= 15) {
    digitalWrite(greenLed, HIGH);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, LOW);
  } 
  
  else {
    digitalWrite(greenLed, LOW);
    digitalWrite(yellowLed, LOW);
    digitalWrite(redLed, LOW);
  }
  
  delay(100);
}

// CED 002, group 06, 2020-14247, 강신의
// CED 002, group 06, 2023-14669, 임태현
// CED 002, group 06, 2025-17066, 김정환
