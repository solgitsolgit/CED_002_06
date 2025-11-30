#pragma once
#include "ttt_solver.h"

// ===== Tic-Tac-Toe Board Scanning (강신의) =====

// 보드 탐색 전 상태 초기화 (위치 기준점, 내부 상태변수 초기화 등)
void tttScanInit();

// 틱택토 보드 9칸을 탐색해서 board에 결과 채움
// - CELL_OTHER: 상대 말(종이컵) 있다고 판단된 칸
// - CELL_EMPTY: 빈 칸
// (내 말은 나중에 BT 입력으로 별도 처리)
void tttScanBoard(BoardState& board);
// ===== End of Tic-Tac-Toe Board Scanning =====