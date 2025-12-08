#include <SoftwareSerial.h> 

// ================= 1. 핀 번호 정의 =================
// [기존 모터/라인센서 핀]
#define ENA 6  
#define EN1 7  
#define EN2 3  

#define ENB 5  
#define EN3 4  
#define EN4 2  

#define LT_MODULE_L A2 
#define LT_MODULE_F A1 
#define LT_MODULE_R A0 

// [조도 센서 핀]
#define PHOTO_PIN A3   
#define PHOTO_TH  300  

// [블루투스 핀 설정]
#define BT_RX 8
#define BT_TX 9
SoftwareSerial btSerial(BT_RX, BT_TX); 

// ★ [추가] LED 핀 정의
#define LED_PIN A2

// ================= 2. 상태 상수 정의 =================
#define CAR_DIR_ST 1 
#define CAR_DIR_FW 2 
#define CAR_DIR_LF 3 
#define CAR_DIR_RF 4 
#define CAR_DIR_UT 5 

// ================= 3. 전역 변수 설정 =================
int speed = 20;
int g_carDirection = CAR_DIR_ST; 

int lastSensorState = 0;
unsigned long lineLostTime = 0; 
#define THRESHOLD 200 
int stop_cnt = 0;
bool is_bt_stopped = false; 

// ================= 4. 초기화 함수 =================
void init_line_tracer_modules(){
  pinMode(LT_MODULE_L, INPUT);
  pinMode(LT_MODULE_F, INPUT);
  pinMode(LT_MODULE_R, INPUT);
}

void setup() {
  Serial.begin(9600);
  btSerial.begin(9600); 
  
  init_line_tracer_modules();
  pinMode(ENA, OUTPUT); pinMode(EN1, OUTPUT); pinMode(EN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(EN3, OUTPUT); pinMode(EN4, OUTPUT); 
  pinMode(PHOTO_PIN, INPUT); 

  // ★ [추가] LED 핀을 출력 모드로 설정
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

// ================= 5. 센서 판단 로직 =================
bool lt_isLeft()    { return (analogRead(LT_MODULE_L) > THRESHOLD); } 
bool lt_isForward() { return (analogRead(LT_MODULE_F) > THRESHOLD); }
bool lt_isRight()   { return (analogRead(LT_MODULE_R) > THRESHOLD); } 

void lt_mode_update()
{
  bool ll = lt_isLeft();
  bool ff = lt_isForward();
  bool rr = lt_isRight(); 

  if (ll || ff || rr) {
    lineLostTime = 0; 
    if (ll) {
      g_carDirection = CAR_DIR_LF;
      lastSensorState = -1; 
    }
    else if (ff) {
      g_carDirection = CAR_DIR_FW;
      lastSensorState = 0; 
    }
    else if (rr) {
      g_carDirection = CAR_DIR_RF;
      lastSensorState = 1; 
    }
  }
  else {
    if (lastSensorState == -1) {
        g_carDirection = CAR_DIR_LF; 
    }
    else if (lastSensorState == 1) {
        g_carDirection = CAR_DIR_RF; 
    }
    else if (lastSensorState == 0) {
      if (lineLostTime == 0) {
        lineLostTime = millis(); 
      }
      unsigned long elapsedTime = millis() - lineLostTime; 
      if (elapsedTime < 10) { 
        g_carDirection = CAR_DIR_FW; 
      }
      else {
        g_carDirection = CAR_DIR_UT; 
      }
    }
  }
}

// ================= 6. 모터 구동 로직 =================
void car_update()
{
  if (g_carDirection == CAR_DIR_FW) 
  {
    digitalWrite(EN1, HIGH); digitalWrite(EN2, LOW); 
    digitalWrite(EN3, HIGH); digitalWrite(EN4, LOW);
    analogWrite(ENA, speed); analogWrite(ENB, speed); 
  }
  else if (g_carDirection == CAR_DIR_LF) 
  {
    digitalWrite(EN1, LOW);  digitalWrite(EN2, HIGH);
    digitalWrite(EN3, HIGH); digitalWrite(EN4, LOW); 
    analogWrite(ENA, speed); analogWrite(ENB, speed);
    delay(90);
  }
  else if (g_carDirection == CAR_DIR_RF) 
  {
    digitalWrite(EN1, HIGH); digitalWrite(EN2, LOW); 
    digitalWrite(EN3, LOW);  digitalWrite(EN4, HIGH);
    analogWrite(ENA, speed); analogWrite(ENB, speed); 
  }
  else if (g_carDirection == CAR_DIR_UT) 
  {
    digitalWrite(EN1, LOW);  digitalWrite(EN2, HIGH); 
    digitalWrite(EN3, HIGH); digitalWrite(EN4, LOW); 
    analogWrite(ENA, speed); analogWrite(ENB, speed);
  }
  else 
  {
    analogWrite(ENA, 0); analogWrite(ENB, 0);
    digitalWrite(EN1, LOW); digitalWrite(EN2, LOW); 
    digitalWrite(EN3, LOW); digitalWrite(EN4, LOW);
  }
}

bool is_dark() {
  return (analogRead(PHOTO_PIN) < PHOTO_TH); 
}

// ================= 7. 메인 루프 =================
void loop(){
  // 0. 블루투스 데이터 수신 확인
  if (btSerial.available()) {
    String cmd = btSerial.readString();
    cmd.trim(); // 공백 제거 

    // ★ [수정] STOP 수신 시: 멈춤 + LED 켜기 (HIGH)
    if (cmd == "STOP" || cmd == "stop") { 
      is_bt_stopped = true; 
      digitalWrite(LED_PIN, HIGH); // LED ON
    }
    // ★ [수정] START 수신 시: 출발 + LED 끄기 (LOW)
    else if (cmd == "START" || cmd == "start") {
      is_bt_stopped = false; 
      digitalWrite(LED_PIN, LOW);  // LED OFF
    }
  }

  // 1. "블루투스 정지 명령" 또는 "어두움" 감지 시 정지
  if (is_bt_stopped || is_dark()) {
    g_carDirection = CAR_DIR_ST;
    car_update(); 
    stop_cnt = 0; 
    return; 
  }

  // 2. 주행 가능 상태면 기존 로직 실행
  stop_cnt++;
  if (stop_cnt < 3){ 
    lt_mode_update(); 
    car_update(); 
  }
  else{
    stop_cnt = 0;
    g_carDirection = CAR_DIR_ST;
    car_update();
  } 
}