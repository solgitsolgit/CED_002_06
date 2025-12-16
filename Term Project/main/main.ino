#include <Arduino.h>

#include "commons.h"
#include "constants.h"
#include "car_hw.h"      // InitHW()
#include "motor.h"       // StopCar() 등
#include "lfs.h"         // lfsInit(), lfsUpdate()
#include "ttt_solver.h"
#include "ttt_scan.h"
#include "us.h"
#include "lcd.h"         // lcdInit(), lcdPrintAnswer()
#include "bt.h"          // btInit(), btPollCommand()

// 블루투스는 car_hw.ino에서 SoftwareSerial btSerial(...) 로 이미 선언/초기화됨
// 여기서 extern으로 가져다 씀
#include <SoftwareSerial.h>
extern SoftwareSerial btSerial;

Mode gMode      = MODE_LFS;   // 현재 모드
Mode gPrevMode  = MODE_LFS;   // 이전 모드 (모드 전환 감지용)

bool gTttDone   = false;      // MODE_TTT에서 Dummy 동작이 끝났는지
BoardState board;
bool isUturn;

void solveTTT(void) {

  int myMoves[5] = {0};
  int myMoveCount = 0;

  btReadNumbersLineBlocking(myMoveCount, myMoves, 9);

  int ans = runTicTacToe(board, myMoves, myMoveCount);
}

// ================== 블루투스 입력 처리 ==================
//
// 현재는 **아주 단순 문자 기반** 프로토콜:
//  - 'l' : LFS 모드로 전환
//  - 't' : 틱택토 모드로 전환
// (원하면 'g', 's' 등으로 마음대로 바꿔도 됨)
// ========================================================

void handleBluetooth() {
  Mode tempMode = btPollCommand();
  if (tempMode != MODE_NULL){
    gMode = tempMode;
  }
}

// ================== setup / loop ==================

void setup() {
  InitHW();           // 모터, 센서, BT, LCD 등 한 번에 초기화
  lfsInit();          // LFS 알고리즘 내부 상태 초기화
  for (int i = 0; i < 9; i++) {
    board.cell[i] = BoardState::CELL_EMPTY;
  }
  tttScanInit(board);      // ttt_scan 초기화
  lcdInit();          // LCD 초기화
  btInit();

  Serial.println("=== System Start ===");
  Serial.println("Mode: LFS (기본)");
}

void loop() {
  // 1. 항상 가장 먼저 BT 입력 확인해서 모드 전환
  //if (gMode != MODE_TTT && gMode != MODE_TTT_MAN) {
  handleBluetooth();
  //}
  bool isDark = IsDark();

  // 2. 모드가 바뀌었는지 확인 (mode enter 시점 처리)
  if (gMode != gPrevMode) {
    Serial.print("[MODE] Change ->");
    if (gMode == MODE_LFS) {
      Serial.println("LFS");
      lfsInit();        // LFS 상태 재초기화 (필요시)
      StopCar();        // 안전하게 정지 후 시작
    }
    else if (gMode == MODE_STOP){
      Serial.println("STOP");
      StopCar();        // 모드 전환 시 항상 정지
    }

    else if (gMode == MODE_SCAN) {
      Serial.println("SCAN");
      isUturn = false;
      StopCar();        // 모드 전환 시 항상 정지
    }

    else if (gMode == MODE_TTT) {
      Serial.println("TTT_Solve");
      gTttDone = false;
      StopCar();        // 모드 전환 시 항상 정지
    }

    else if (gMode == MODE_TTT_MAN){
      Serial.println("TTT_Manual");
      StopCar();        // 모드 전환 시 항상 정지
    }
    Serial.println("\n");
    
    gPrevMode = gMode;
  }

  // 3. 현재 모드에 따라 동작
  switch (gMode) {
    case MODE_LFS:
      // LFS 모드: 계속 라인트레이싱 주행
      if (!isDark){
        lfsUpdate();
      }
      else {
        StopCar();
      }
      break;

    case MODE_STOP:
      StopCar();
      break;
    
    case MODE_SCAN:
    // Implement scan mode
      isUturn = lfsUpdate();
      float ld = usReadLeftCm();
      float rd = usReadRightCm();
      tttScanBoard(board, isUturn, rd, ld);
      break;

    case MODE_TTT:
      StopCar();
      if (!gTttDone) {
        solveTTT();
        gTttDone = true;

        delay(1000);
        gMode = MODE_STOP;
      }
      // 이후에는 제자리에서 아무것도 안 함 (필요하면 정지 유지)
      break;

    default:
      gMode = MODE_STOP;
  }

  // 필요시 아주 짧은 delay (너무 빡빡하면 Serial 출력이 꼬일 수 있음)
  delay(5);
}
