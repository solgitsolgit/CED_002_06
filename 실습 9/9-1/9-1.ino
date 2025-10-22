#define Forward 1 // 전진
#define Backward 2 // 후진
#define Turn_Right 3 // 우회전
#define Turn_Left 4 // 좌회전
#define Stop 5 // 정지

int direction = 0; // 차량 운행상태 전역변수 선언
int speed = 200;

#define ENA 6
#define EN1 7
#define EN2 3
#define EN3 4
#define EN4 2
#define ENB 5

void setup() {
  pinMode(ENA, OUTPUT); // ENA
  pinMode(EN1, OUTPUT); // EN1
  pinMode(EN2, OUTPUT); // EN2
  pinMode(ENB, OUTPUT); // ENB
  pinMode(EN3, OUTPUT); // EN3
  pinMode(EN4, OUTPUT); // EN4
}

void loop() {
  delay(1000); // 1초 delay
  direction = direction + 1; // 방향 전환 시 사용되는 변수

  if(direction == Forward) // 전진 주행
  {
    digitalWrite(EN1, HIGH);
    digitalWrite(EN2, LOW);
    analogWrite(ENA, speed);
    digitalWrite(EN3, HIGH);
    digitalWrite(EN4, LOW);
    analogWrite(ENB, speed);
  }

  else if(direction == Backward) // 후진 주행
  {
    digitalWrite(EN1, LOW);
    digitalWrite(EN2, HIGH);
    analogWrite(ENA, speed);
    digitalWrite(EN3, LOW);
    digitalWrite(EN4, HIGH);
    analogWrite(ENB, speed);
  }

  else if(direction == Turn_Right)
  {
    digitalWrite(EN1, HIGH);
    digitalWrite(EN2, LOW);
    analogWrite(ENA, speed);
    digitalWrite(EN3, LOW);
    digitalWrite(EN4, HIGH);
    analogWrite(ENB, speed);
  }

  else if(direction == Turn_Left)
  {
    digitalWrite(EN1, LOW);
    digitalWrite(EN2, HIGH);
    analogWrite(ENA, speed);
    digitalWrite(EN3, HIGH);
    digitalWrite(EN4, LOW);
    analogWrite(ENB, speed);
  }

  else if(direction == Stop)
  {
    digitalWrite(EN1, LOW);
    digitalWrite(EN2, LOW);
    analogWrite(ENA, 0);
    digitalWrite(EN3, LOW);
    digitalWrite(EN4, LOW);
    analogWrite(ENB, 0);
  }
}