#pragma once

#include "commons.h"

// board: 전체 9칸 상태 (CELL_EMPTY, CELL_MINE, CELL_OTHER)
// myMoves: 블루투스로 받은 "내가 이미 둔 위치들" (1~9 값들)
// myMoveCount: myMoves 배열에 들어있는 개수
//
// 반환값: 이기기 위해 지금 둬야 할 위치 (1~9)
//         만약 당장 이기는 수가 없다면 -1 반환
int tttFindWinningMove(const BoardState& board,
                       const int myMoves[],
                       int myMoveCount);
// ===== End of Tic-Tac-Toe Solver =====