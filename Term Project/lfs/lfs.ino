#include <Arduino.h>
#include "CarHW.h"
#include "line_sensor.h"
#include "motor.h"

// 방향 상태
#define CAR_DIR_ST  1
#define CAR_DIR_FW  2
#define CAR_DIR_LF  3
#define CAR_DIR_RF  4
#define CAR_DIR_UT  5   // 유턴(180도)

// 튜닝 값(필요시 조절)
static const int LOOP_DELAY_MS   = 100;  // 원본 코드처럼 100ms
static const int TURN_MS         = 170;  // 좌/우 회전 시간(너의 TurnLeft/Right가 "회전 시작"만 하면 필요)
static const int REACQUIRE_MS    = 120;  // 회전 후 라인 다시 잡기용 전진
static const int BACK_MS_UTURN   = 120;  // 유턴 전 살짝 후진
static const int LOST_CONFIRM    = 3;    // 라인 미검출 연속 N번이면 진짜 막다른 길로 판단
static const int UTURN_COOLDOWN  = 400;  // 유턴 연타 방지(ms)

static int      g_carDirection = CAR_DIR_ST;
static int      g_lostCount    = 0;
static uint32_t g_lastUTurnMs  = 0;

static inline bool lsLeft(uint8_t v)   { return (v & LINE_LEFT)   != 0; }
static inline bool lsFront(uint8_t v)  { return (v & LINE_CENTER) != 0; }
static inline bool lsRight(uint8_t v)  { return (v & LINE_RIGHT)  != 0; }

static bool isJunction(uint8_t v) {
  // 1) 3개 센서 모두 검정(교차로) 판단 함수 우선 사용
  if (lineIsIntersection(v)) return true;

  // 2) 또는 2개 이상 동시에 감지되면 교차로/분기점으로 간주
  int cnt = 0;
  if (lsLeft(v))  cnt++;
  if (lsFront(v)) cnt++;
  if (lsRight(v)) cnt++;
  return (cnt >= 2);
}

static void lfs_mode_update() {
  // IsLT()로 라인 존재 여부를 먼저 판단(없으면 막다른 길 후보)
  if (!IsLT()) {
    g_lostCount++;
    if (g_lostCount >= LOST_CONFIRM) g_carDirection = CAR_DIR_UT;
    else g_carDirection = CAR_DIR_FW; // 잠깐 끊김은 전진으로 버텨보기(원하면 ST로 바꿔도 됨)
    return;
  }
  g_lostCount = 0;

  uint8_t v = lineRead();
  bool L = lsLeft(v);
  bool F = lsFront(v);
  bool R = lsRight(v);

  // 교차로에서는 LFS 규칙: 좌 -> 전 -> 우 -> 유턴
  if (isJunction(v)) {
    if (L)       g_carDirection = CAR_DIR_LF;
    else if (F)  g_carDirection = CAR_DIR_FW;
    else if (R)  g_carDirection = CAR_DIR_RF;
    else         g_carDirection = CAR_DIR_UT;
    return;
  }

  // 교차로가 아니면 간단 라인트레이싱(중앙 우선)
  if (F)         g_carDirection = CAR_DIR_FW;
  else if (L)    g_carDirection = CAR_DIR_LF;
  else if (R)    g_carDirection = CAR_DIR_RF;
  else           g_carDirection = CAR_DIR_UT;
}

static void car_update() {
  if (g_carDirection == CAR_DIR_FW) {          // 전진
    MoveFront();
  }
  else if (g_carDirection == CAR_DIR_LF) {     // 좌회전
    TurnLeft();
    delay(TURN_MS);
    MoveFront();
    delay(REACQUIRE_MS);
  }
  else if (g_carDirection == CAR_DIR_RF) {     // 우회전
    TurnRight();
    delay(TURN_MS);
    MoveFront();
    delay(REACQUIRE_MS);
  }
  else if (g_carDirection == CAR_DIR_UT) {     // 유턴(180도)
    uint32_t now = millis();
    if (now - g_lastUTurnMs < (uint32_t)UTURN_COOLDOWN) {
      StopCar();
      return;
    }
    g_lastUTurnMs = now;

    StopCar();
    delay(50);

    MoveBack();                // 유턴 전 살짝 후진(선에서 벗어난 상태 정리)
    delay(BACK_MS_UTURN);
    StopCar();
    delay(50);

    motorTurnAround180();      // ★ 요구사항: 180도 회전 유턴

    StopCar();
    delay(50);

    MoveFront();               // 유턴 후 라인 재획득
    delay(REACQUIRE_MS);
  }
  else {                                       // 정지
    StopCar();
  }
}

// LFS 주행 시작 전에 호출 (필요한 상태 변수 초기화)
void lfsInit(){
  lineSensorInit();
  SetSpeed(currentSpeed);   // CarHW.h의 currentSpeed 사용
  StopCar();

  g_carDirection = CAR_DIR_ST;
  g_lostCount = 0;
  g_lastUTurnMs = 0;
}

// main loop에서 MODE_LFS일 때 반복적으로 호출
void lfsUpdate(){
  lfs_mode_update();
  car_update();
  delay(LOOP_DELAY_MS);     // 원본 코드 스타일 유지
}