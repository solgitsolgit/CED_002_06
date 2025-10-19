int speed = 200; // 모터 속도 설정 (0 ~ 255)

#define ENA 6 // 모터 1,2 속도 제어, S6
#define ENB 5 // 모터 3,4 속도 제어, S5
#define IN1 7 // 모터 1, S7
#define IN2 3 // 모터 2, S3
#define IN3 4 // 모터 3, S4
#define IN4 2 // 모터 4, S2

void setup() {
  // pin 모드 출력으로 설정
  pinMode(ENA, OUTPUT); 
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {
  analogWrite(ENA, speed); // 모터 1,2 속도 설정
  analogWrite(ENB, speed); // 모터 3,4 속도 설정

  digitalWrite(IN1, HIGH); // 모터 1 제어
  digitalWrite(IN2, LOW); // 모터 2 제어
  digitalWrite(IN3, HIGH); // 모터 3 제어
  digitalWrite(IN4, LOW); // 모터 4 제어

  // delay(1000);
}

// CED 002, group 06, 2020-14247, ShinYee Kang
// CED 002, group 06, 2023-14669, TaeHyun Lim
// CED 002, group 06, 2025-17066, JungHwan Kim