#include "CarHW.h"

// 블루투스 수신 버퍼
String bt_buffer = "";
String last_msg = "Waiting...";   // LCD 2번째 줄 저장용
bool is_connected = false;        // 연결 상태 플래그

void setup() {
  InitHW();      
  SetSpeed(0);   
  
  Serial.println("--- All Sensor Debug Monitor ---");
  Serial.println("L:Left_Dist | R:Right_Dist | P:Photo | BT:Bluetooth");
  
  // [LCD 초기 화면]
  // 첫 줄: 상태, 둘째 줄: 대기 중 메시지
  DisplayLCD("BT Status: --", "Cmd: None");
}

void loop() {
  // ==========================================
  // 1. 센서 값 읽기 (시리얼 모니터용)
  // ==========================================
  long leftDist = GetLeftDistance();
  long rightDist = GetRightDistance();
  int photoValue = ReadPhotoSensor();
  bool isDark = IsDark();

  // ==========================================
  // 2. 블루투스 수신 및 LCD 업데이트
  // ==========================================
  char receivedChar = GetBT(); // 헤더파일의 함수 사용
  
  if (receivedChar != 0) {
      bt_buffer += receivedChar;
      
      // 엔터(명령어 끝)가 들어오면 LCD 갱신
      if (receivedChar == '\n' || receivedChar == '\r') {
         // 공백 문자 제거 (trim)
         bt_buffer.trim();
         
         if (bt_buffer.length() > 0) {
             last_msg = bt_buffer; // 마지막 메시지 저장
             is_connected = true;  // 데이터를 받았으므로 연결됨으로 판단
             
             // ★ LCD 업데이트 (이곳에서만 갱신)
             // 줄 1: 연결됨 표시
             // 줄 2: 수신된 명령어 표시
             DisplayLCD("BT Status: OK", last_msg);
             
             // 시리얼 모니터에도 로깅
             Serial.print("[BT RX]: ");
             Serial.println(last_msg);
         }
         bt_buffer = ""; // 버퍼 비우기
      }
  }
  
  // ==========================================
  // 3. 시리얼 모니터 출력 (센서 값 확인용)
  // ==========================================
  // 너무 빠르면 보기 힘들므로 0.3초마다 출력
  static unsigned long serial_timer = 0;
  if (millis() - serial_timer > 300) {
      Serial.print("L:"); Serial.print(leftDist);
      Serial.print("cm | R:"); Serial.print(rightDist);
      Serial.print("cm | P:"); Serial.print(photoValue);
      Serial.println(isDark ? " (Dark)" : " (Bright)");
      
      serial_timer = millis();
  }
  
  // 더 이상 LCD에 센서값을 덮어쓰지 않음
}