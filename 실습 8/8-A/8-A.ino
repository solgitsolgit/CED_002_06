// motor 설정
int speed = 200; // 모터 속도 설정 (0 ~ 255)

#define ENA 6 // 모터 1,2 속도 제어, S6
#define ENB 5 // 모터 3,4 속도 제어, S5
#define IN1 7 // 모터 1, S7
#define IN2 3 // 모터 2, S3
#define IN3 4 // 모터 3, S4
#define IN4 2 // 모터 4, S2

// line tracer sensor 설정
#define LineSensor A0 // 핀 설정
const int Threshold = 500; // 임계값 설정

void setup() {
  // pin 모드 출력으로 설정
  pinMode(ENA, OUTPUT); 
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // motor 방향 설정
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW); 
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// motor를 멈추는 함수
void stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

// motor를 구동시키는 함수
void move() {
  analogWrite(ENA, speed); 
  analogWrite(ENB, speed);
}

void loop() {
  int sensorValue = analogRead(LineSensor); // 센서 값 읽기
  Serial.print(sensorValue); // 시리얼 모니터에 출력

  if (sensorValue > Threshold) {
    move();
    Serial.println ("black -> move"); // 검은색 라인 위 모터 구동
  }

  else { 
    stop();
    Serial.println("white -> stop"); // 흰색 바닥 위 모터 멈춤
  } 

  delay(100);
}

// CED 002, group 06, 2020-14247, ShinYee Kang
// CED 002, group 06, 2023-14669, TaeHyun Lim
// CED 002, group 06, 2025-17066, JungHwan Kim