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


Mode gMode      = MODE_LFS;   // 현재 모드
Mode gPrevMode  = MODE_LFS;   // 이전 모드 (모드 전환 감지용)

bool gTttDone   = false;      // MODE_TTT에서 Dummy 동작이 끝났는지
BoardState board;
bool isUturn;

static bool btLocked = false;

int myMoveCount = 0;
int myMoves[9] = {0};

void handleBluetooth() {
  Mode temp = btPollCommand(&myMoveCount, myMoves, 9);
  if (temp != MODE_NULL) {
    gMode = temp;

    // ===== 디버깅 출력 =====
    if (gMode == MODE_TTT) {
      Serial.println("[BT] MODE_TTT received");
      Serial.print("[BT] myMoveCount = ");
      Serial.println(myMoveCount);

      Serial.print("[BT] myMoves = ");
      for (int i = 0; i < myMoveCount; i++) {
        Serial.print(myMoves[i]);
        if (i + 1 < myMoveCount) Serial.print(", ");
      }
      Serial.println();
    }
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
  if (!btLocked) {
    handleBluetooth();
  }
  bool isDark = IsDark();

  // 2. 모드가 바뀌었는지 확인 (mode enter 시점 처리)
  if (gMode != gPrevMode) {
    if (gPrevMode != MODE_STOP){
      LED_Off();
    }
    Serial.print("[MODE] Change ->");
    if (gMode == MODE_LFS) {
      Serial.println("LFS");
      LED_Off();
      lfsInit();        // LFS 상태 재초기화 (필요시)
      StopCar();        // 안전하게 정지 후 시작
    }
    else if (gMode == MODE_STOP){
      Serial.println("STOP");
      LED_On();
      StopCar();        // 모드 전환 시 항상 정지
    }

    else if (gMode == MODE_SCAN) {
      LED_Off();
      Serial.println("SCAN");
      isUturn = false;
      StopCar();        // 모드 전환 시 항상 정지
    }

    else if (gMode == MODE_TTT) {
      btLocked = true; // TTT 모드 진입 시 BT 잠금
      LED_Off();
      Serial.println("TTT_Solve");
      gTttDone = false;
      StopCar();
    }

    else if (gMode == MODE_TTT_MAN){
      btLocked = true;
      LED_Off();
      Serial.println("TTT_Manual");
      StopCar();        // 모드 전환 시 항상 정지
    }
    
    gPrevMode = gMode;
  }

  // 3. 현재 모드에 따라 동작
  switch (gMode) {
    case MODE_LFS:{
      // LFS 모드: 계속 라인트레이싱 주행
      if (!isDark){
        lfsUpdate();
      }
      else {
        StopCar();
      }
      break;
    }

    case MODE_STOP:{
      StopCar();
      break;
    }
    
    case MODE_SCAN:{
    // Implement scan mode
      isUturn = lfsUpdate();
      float ld = usReadLeftCm();
      delay(10);
      float rd = usReadRightCm();
      bool isScanDone = tttScanBoard(board, isUturn, rd, ld);
      //Serial.println("SCAN L:" + String(ld) + " R:" + String(rd));
      if (isScanDone) {
        Serial.println("[SCAN] Done. Board state:");
        for (int i = 0; i < 9; ++i) {
          Serial.print(String(board.cell[i]) + " ");
        }
        Serial.println();
        gMode = MODE_STOP;
      }
      
      break;
    }

    case MODE_TTT:{
      Serial.println("[TTT] Solving...");
      StopCar();
      int ans = solveTTT(board, myMoves, myMoveCount);
      Serial.println("[TTT] Answer: " + String(ans));
      gTttDone = true;

      btLocked = false;
      break;
    }

    case MODE_TTT_MAN:{
      Serial.println("[TTT] Solving...");
      StopCar();
      int myMove_man = 0;
      int myMoves_man[9] = {0};

      for (int i = 0; i < 9; i++) {
        board.cell[i] = myMoves[i];
        if (myMoves[i] == BoardState::CELL_MINE) {
          myMoves_man[myMove_man++] = i+1;
      }
    }

      int ans = runTicTacToe(board, myMoves_man, myMove_man);
      Serial.println("[TTT] Answer: " + String(ans));
      gTttDone = true;

      btLocked = false;
      break;
    }

    default:{
      StopCar();
      break;
    }
  }

  if ((gMode == MODE_TTT && gTttDone) || (gMode == MODE_TTT_MAN)) {
    gMode = MODE_STOP;
  }

  // 필요시 아주 짧은 delay (너무 빡빡하면 Serial 출력이 꼬일 수 있음)
  delay(5);
}
