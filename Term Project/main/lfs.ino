#include "lfs.h"

/*
// ================= 1. 핀 번호 정의 =================
#define ENA 6  // 왼쪽 모터 속도 (PWM)
#define EN1 7  // 왼쪽 방향 1
#define EN2 3  // 왼쪽 방향 2

#define ENB 5  // 오른쪽 모터 속도 (PWM)
#define EN3 4  // 오른쪽 방향 1
#define EN4 2  // 오른쪽 방향 2

#define LT_MODULE_L A2 // 왼쪽 센서
#define LT_MODULE_F A1 // 중앙 센서
#define LT_MODULE_R A0 // 오른쪽 센서

*/

// ================= 2. 상태 상수 정의 =================
#define CAR_DIR_ST 1 // 정지
#define CAR_DIR_FW 2 // 전진
#define CAR_DIR_LF 3 // 좌회전
#define CAR_DIR_RF 4 // 우회전
#define CAR_DIR_UT 5 // 유턴

// ================= 3. 전역 변수 설정 =================
// 속도: 배터리 상태에 따라 150 ~ 255 사이로 조절하세요.
int speed = 20; 
bool was_left = false;
// 현재 자동차의 동작 상태
int g_carDirection = CAR_DIR_ST;

// [핵심] 직전 상태 기억 변수 (-1:왼쪽, 0:직진, 1:오른쪽)
int lastSensorState = 0; 

// [핵심] 선을 놓친 시점을 기록할 타이머 변수
unsigned long lineLostTime = 0; 

// 센서 감도 기준값 (환경에 따라 100~800 사이 조정)
#define THRESHOLD 200 
int stop_cnt = 0;

// ================= 4. 초기화 함수 =================
void init_line_tracer_modules(){
  pinMode(LT_MODULE_L, INPUT);
  pinMode(LT_MODULE_F, INPUT);
  pinMode(LT_MODULE_R, INPUT);
}

void lfsInit() {
  Serial.begin(9600);
  init_line_tracer_modules();

  pinMode(ENA, OUTPUT); pinMode(EN1, OUTPUT); pinMode(EN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(EN3, OUTPUT); pinMode(EN4, OUTPUT);
  
  // LCD 등 다른 센서 초기화가 필요하면 여기에 추가
}


// ================= 5. 센서 판단 로직 =================
// 센서 값을 읽어서 True(검은선)/False(흰색) 반환
bool lt_isLeft()    { return (analogRead(LT_MODULE_L) > THRESHOLD); }
bool lt_isForward() { return (analogRead(LT_MODULE_F) > THRESHOLD); }
bool lt_isRight()   { return (analogRead(LT_MODULE_R) > THRESHOLD); }

bool lt_mode_update()
{
  bool ll = lt_isLeft();
  bool ff = lt_isForward();
  bool rr = lt_isRight();

  // Case 1: 선이 감지되는 상황 (정상 주행)
  // 선이 보이면 타이머를 리셋하고, 현재 방향을 기억합니다.
  if (ll || ff || rr) {
    lineLostTime = 0; // 선 찾음 -> 타이머 초기화

    // 우선순위: 왼쪽(LFS) > 직진 > 오른쪽
    if (ll) {
      g_carDirection = CAR_DIR_LF;
      lastSensorState = -1; // "방금 왼쪽이었음"
    }
    else if (ff) {
      g_carDirection = CAR_DIR_FW;
      lastSensorState = 0;  // "방금 직진이었음"
    }
    else if (rr) {
      g_carDirection = CAR_DIR_RF;
      lastSensorState = 1;  // "방금 오른쪽이었음"
    }
  }
  
  // Case 2: 선이 하나도 안 보이는 상황 (0, 0, 0)
  // "기억"을 되살려서 판단합니다.
  else {
    // (A) 회전 중에 놓친 경우 -> 관성 유지 (계속 돌아서 선 찾기)
    if (lastSensorState == -1) {
        g_carDirection = CAR_DIR_LF; 
    }
    else if (lastSensorState == 1) {
        g_carDirection = CAR_DIR_RF;
    }
    
    // (B) 직진 중에 놓친 경우 -> 틈(Gap)인지 막다른 길(Dead End)인지 시간으로 판단
    else if (lastSensorState == 0) {
      
      // 처음 놓친 순간이라면 시간 기록 시작
      if (lineLostTime == 0) {
        lineLostTime = millis(); 
      }

      // 경과 시간 계산
      unsigned long elapsedTime = millis() - lineLostTime;

      // 0.2초(200ms) 동안은 "잠깐 끊긴 거겠지" 하고 직진 유지
      if (elapsedTime < 10) { 
        g_carDirection = CAR_DIR_FW; 
      }
      // 0.2초가 지났는데도 선이 안 나타나면 "아, 진짜 막다른 길이구나" -> 유턴
      else {
        bool flag = (g_carDirection != CAR_DIR_UT);
        g_carDirection = CAR_DIR_UT;
        return flag;
      }
    }
  }
  return false;
}


// ================= 6. 모터 구동 로직 =================
void car_update()
{
  if (g_carDirection == CAR_DIR_FW) // [전진]
  {
    digitalWrite(EN1, HIGH); digitalWrite(EN2, LOW); // 왼쪽 전진
    digitalWrite(EN3, HIGH); digitalWrite(EN4, LOW); // 오른쪽 전진
    analogWrite(ENA, speed); analogWrite(ENB, speed);
  }
  else if (g_carDirection == CAR_DIR_LF) // [좌회전] (제자리 회전)
  {
    digitalWrite(EN1, LOW);  digitalWrite(EN2, HIGH); // 왼쪽 후진
    digitalWrite(EN3, HIGH); digitalWrite(EN4, LOW);  // 오른쪽 전진
    analogWrite(ENA, speed); analogWrite(ENB, speed);
    delay(100);
  }
  else if (g_carDirection == CAR_DIR_RF) // [우회전] (제자리 회전)
  {
    digitalWrite(EN1, HIGH); digitalWrite(EN2, LOW);  // 왼쪽 전진
    digitalWrite(EN3, LOW);  digitalWrite(EN4, HIGH); // 오른쪽 후진
    analogWrite(ENA, speed); analogWrite(ENB, speed);
  }
  else if (g_carDirection == CAR_DIR_UT) // [유턴] (강한 제자리 회전)
  {
    digitalWrite(EN1, HIGH); digitalWrite(EN2, LOW);  // 왼쪽 전진
    digitalWrite(EN3, LOW);  digitalWrite(EN4, HIGH); // 오른쪽 후진
    analogWrite(ENA, speed); analogWrite(ENB, speed);
  }
  else // [정지] (CAR_DIR_ST)
  {
    analogWrite(ENA, 0); analogWrite(ENB, 0);
    // 모터 풀림 방지 (Brake)
    digitalWrite(EN1, LOW); digitalWrite(EN2, LOW);
    digitalWrite(EN3, LOW); digitalWrite(EN4, LOW);
  }
}


// ================= 7. 메인 루프 =================
bool lfsUpdate(){
  stop_cnt++;
  bool ret = false;
  if (stop_cnt < 3){
  ret = lt_mode_update(); // 센서 판단 및 방향 결정
  car_update();     // 모터 구동
  
  // 딜레이를 최소화하여 반응 속도 향상 (10ms 권장)
  }
  //delay(100);
  else{
    g_carDirection = CAR_DIR_ST;
    car_update();
    stop_cnt = 0;
  }

  return ret;
}