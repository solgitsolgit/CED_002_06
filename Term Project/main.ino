#include "car_hw.h"
#include "ttt_solver.h"

// 전역 상태
Mode gMode = MODE_LFS;
BoardState gBoard;
int gMyMoves[5];
int gMyMoveCount = 0;

void setup() {
  motorInit();
  lineSensorInit();
  btInit();
  usInit();
  lcdInit();
  lfsInit();
  tttScanInit();
  // 기타 초기화...
}

void loop() {
  // 1. 항상 BT 체크
  BtCommand cmd = btPollCommand();
  // cmd 처리해서 gMode 전환 등...

  switch (gMode) {
    case MODE_LFS:
      lfsUpdate();
      break;

    case MODE_WAIT_BT:
      // motorStop(); 정도 유지
      break;

    case MODE_TTT_SCAN:
      tttScanBoard(gBoard);
      lcdPrintBoard(gBoard);
      gMode = MODE_TTT_SOLVE;
      break;

    case MODE_TTT_SOLVE:
      // btReadMove()로 내 말 위치들 gMyMoves에 채운 뒤
      int ans = tttFindWinningMove(gBoard, gMyMoves, gMyMoveCount);
      lcdPrintAnswer(ans);
      // 이후 모드 전환…
      break;
  }
}
