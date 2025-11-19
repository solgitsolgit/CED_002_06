#pragma once
// ===== Tic-Tac-Toe Solver (임태현) =====

// Board 상태 표현 (아래는 예시, 원하는 대로 구조체 만들어주세요)
// 사용 예시:
// BoardState board;
// board.cells[0] = BoardState::CELL_MINE; // 1번 칸에 내 돌
// board.cells[1] = BoardState::CELL_OTHER; // 2번 칸에 상대 돌
// board.cells[2] = BoardState::CELL_EMPTY; // 3번 칸 비어있음
struct BoardState {
    enum CellState {
        CELL_EMPTY,
        CELL_MINE,
        CELL_OTHER
    };
    CellState cells[9];
};

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