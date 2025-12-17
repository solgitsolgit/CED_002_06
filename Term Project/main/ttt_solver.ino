#include "ttt_solver.h"

// ===== 기존 조원 코드 기반 (약간의 버그/누락 보완 포함) =====
static const uint16_t WIN_MASKS[8] = {
  0b000000111, // 1행
  0b000111000, // 2행
  0b111000000, // 3행
  0b001001001, // 1열
  0b010010010, // 2열
  0b100100100, // 3열
  0b001010100, // 대각선 (1,5,9)
  0b100010001  // 대각선 (3,5,7)  <-- 원본에 빠져있던 케이스 보완
};

static inline uint16_t bitOfPos(int pos1to9) {
  return (pos1to9 >= 1 && pos1to9 <= 9)
         ? (uint16_t)(1u << (pos1to9 - 1))
         : (uint16_t)0;
}

static bool isWin(uint16_t mask) {
  for (int i = 0; i < 8; i++) {
    if ((mask & WIN_MASKS[i]) == WIN_MASKS[i]) return true;
  }
  return false;
}

static int findBestMove(uint16_t myMask, uint16_t oppMask, uint16_t allMask) {
  // 1) 이길 수 있으면 이기는 수
  for (int pos = 1; pos <= 9; pos++) {
    uint16_t b = bitOfPos(pos);
    if (allMask & b) continue;
    if (isWin(myMask | b)) return pos;
  }

  // 2) 상대가 다음에 이기는 수 있으면 막기
  for (int pos = 1; pos <= 9; pos++) {
    uint16_t b = bitOfPos(pos);
    if (allMask & b) continue;
    if (isWin(oppMask | b)) return pos;
  }

  // 3) 그 외 정책: 지금은 -1 (원하면 센터/코너 선호 등 넣을 수 있음)
  return -1;
}

// ===== 네가 요구한 I/O에 맞춘 래퍼 =====
int runTicTacToe(const BoardState& board,
                 const int myMoves[],
                 int myMoveCount)
{
  // 0) allMask 구성: 보드에 말이 있는 칸 (OTHER로 들어옴)
  uint16_t allMask = 0;
  for (int i = 0; i < 9; i++) {
    if (board.cell[i] != BoardState::CELL_EMPTY) {
      allMask |= (uint16_t)(1u << i);  // i=0이 pos1
    }
  }

  // 1) myMask 구성: myMoves[]에 있는 칸들만 MINE으로 override
  //    - 단, 그 칸이 allMask(즉 말이 존재) 안에 있는 경우만 인정
  uint16_t myMask = 0;
  for (int k = 0; k < myMoveCount; k++) {
    int pos = myMoves[k];         // 1~9
    uint16_t b = bitOfPos(pos);
    if (b == 0) continue;
    if (allMask & b) {            // 그 칸에 말이 있어야 내 말로 인정
      myMask |= b;
    }
  }

  // 2) 상대 마스크
  uint16_t oppMask = allMask & (uint16_t)(~myMask);

  // 3) 최적 수 계산
  int ans = findBestMove(myMask, oppMask, allMask);

  // 4) 디버깅 로그 (원하면 지워도 됨)
  Serial.print("[TTT] allMask="); Serial.println(allMask, BIN);
  Serial.print("[TTT] myMask ="); Serial.println(myMask, BIN);
  Serial.print("[TTT] oppMask="); Serial.println(oppMask, BIN);
  Serial.print("[TTT] ans="); Serial.println(ans);

  // 5) LCD 출력은 여기서 해도 되고, main에서 해도 됨.
  //    요구사항대로 "1~9" 출력.
  lcdDisplayMessage("TTT Next Move", ("ANS: " + String(ans)).c_str());

  return ans;
}

int solveTTT(BoardState& board, int myMoves[], int myMoveCount) {
  int ans = runTicTacToe(board, myMoves, myMoveCount);
  
}