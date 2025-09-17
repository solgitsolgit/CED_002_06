const int MicPin = 2; // Mic 센서 핀 설정
const int MotionPin = 3; // 모션센서 핀 설정
const int LightPin = A0; // 광센서 핀 설정

const int RedPin = 5;
const int YellowPin = 6;
const int GreenPin = 7;

const int Threshold = 600; // 광센서 임계값 설정

void setup() {
  pinMode(MicPin, INPUT);
  pinMode(MotionPin, INPUT);
  pinMode(LightPin, INPUT); // 센서 핀들은 입력으로 설정

  pinMode(RedPin, OUTPUT);
  pinMode(YellowPin, OUTPUT);
  pinMode(GreenPin, OUTPUT); // Led 핀들은 출력으로 설정
}

void loop() {
  int MicState = digitalRead(MicPin);
  int MotionState = digitalRead(MotionPin);
  int LightValue = analogRead(LightPin); // 센서 값 읽기

  if (MicState == HIGH) {
    digitalWrite(RedPin, HIGH);
  } else {
    digitalWrite(RedPin, LOW);
  } // Mic 센서에 신호가 들어오면 RedLed 점등

  if (MotionState == HIGH) {
    digitalWrite(YellowPin, HIGH);
  } else {
    digitalWrite(YellowPin, LOW);
  }  // 모션센서에 신호가 들어오면 YellowLed 점등

  if (LightValue > Threshold) {
    digitalWrite(GreenPin, HIGH);
  } else {
    digitalWrite(GreenPin, LOW);
  }
  // 광센서에 신호가 들어오면 GreenLed 점등

  delay(1000);
}

// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066