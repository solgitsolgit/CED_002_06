#include <Arduino.h>

#include "constants.h"
#include "car_hw.h"      // InitHW()
#include "motor.h"       // StopCar() 등
#include "lfs.h"         // lfsInit(), lfsUpdate()

// 블루투스는 car_hw.ino에서 SoftwareSerial btSerial(...) 로 이미 선언/초기화됨
// 여기서 extern으로 가져다 씀
#include <SoftwareSerial.h>
extern SoftwareSerial btSerial;

// (나중에 진짜 구현할 틱택토 관련 헤더들)
// #include "ttt_scan.h"
// #include "ttt_solve.h"
// #include "lcd_xxx.h" ...

// ================== 모드 정의 ==================

enum Mode {
  MODE_LFS = 0,      // Left-First-Search 라인트레이싱 모드
  MODE_TTT           // 틱택토 탐색 & 정답 출력 모드 (현재는 dummy)
};

Mode gMode      = MODE_LFS;   // 현재 모드
Mode gPrevMode  = MODE_LFS;   // 이전 모드 (모드 전환 감지용)

bool gTttDone   = false;      // MODE_TTT에서 Dummy 동작이 끝났는지

// ================== 틱택토 Dummy 함수들 ==================

// 실제로는:
//  - 초음파로 9칸 탐색 (tttScanBoard(board))
//  - BT로 내 말 위치 입력
//  - tttFindWinningMove() 호출
//  - LCD에 정답 출력
// 이런 구조가 들어갈 자리.
void runTicTacToeDummy() {
  Serial.println("[TTT] Dummy: 틱택토 스캔 & 정답 출력 자리입니다.");
  Serial.println("[TTT] (나중에 초음파 + 보드 탐색 + 정답 알고리즘 들어갈 예정)");

  // 나중에 여기서:
  // BoardState board;
  // tttScanInit(board);
  // tttScanBoard(board);
  // int ans = tttFindWinningMove(board, ...);
  // lcdPrintAnswer(ans);
}

// ================== 블루투스 입력 처리 ==================
//
// 현재는 **아주 단순 문자 기반** 프로토콜:
//  - 'l' : LFS 모드로 전환
//  - 't' : 틱택토 모드로 전환
// (원하면 'g', 's' 등으로 마음대로 바꿔도 됨)
// ========================================================

void handleBluetooth() {
  if (btSerial.available() > 0) {
    char c = btSerial.read();

    // 디버깅용: PC 시리얼에도 에코하고 싶다면
    Serial.print("[BT] Received: ");
    Serial.println(c);

    if (c == 'l') {
      gMode = MODE_LFS;
    } else if (c == 't') {
      gMode = MODE_TTT;
    }

    // 필요시 다른 커맨드들도 여기서 처리 가능 (예: 속도 조절 등)
  }
}

// ================== setup / loop ==================

void setup() {
  InitHW();          // 모터, 센서, BT, LCD 등 한 번에 초기화
  lfsInit();         // LFS 알고리즘 내부 상태 초기화

  Serial.println("=== System Start ===");
  Serial.println("Mode: LFS (기본)");
  Serial.println("Bluetooth: 'l' = LFS, 't' = TicTacToe");
}

void loop() {
  // 1. 항상 가장 먼저 BT 입력 확인해서 모드 전환
  handleBluetooth();

  // 2. 모드가 바뀌었는지 확인 (mode enter 시점 처리)
  if (gMode != gPrevMode) {
    Serial.print("[MODE] Change -> ");
    if (gMode == MODE_LFS) {
      Serial.println("LFS");
      lfsInit();        // LFS 상태 재초기화 (필요시)
      StopCar();        // 안전하게 정지 후 시작
    } else if (gMode == MODE_TTT) {
      Serial.println("TicTacToe (Dummy)");
      gTttDone = false;
      StopCar();        // 모드 전환 시 항상 정지
    }
    gPrevMode = gMode;
  }

  // 3. 현재 모드에 따라 동작
  switch (gMode) {
    case MODE_LFS:
      // LFS 모드: 계속 라인트레이싱 주행
      lfsUpdate();
      break;

    case MODE_TTT:
      // 지금은 Dummy: 한 번만 실행하고 끝
      if (!gTttDone) {
        runTicTacToeDummy();
        gTttDone = true;
      }
      // 이후에는 제자리에서 아무것도 안 함 (필요하면 정지 유지)
      StopCar();
      break;
  }

  // 필요시 아주 짧은 delay (너무 빡빡하면 Serial 출력이 꼬일 수 있음)
  delay(5);
}
