#include "ttt_scan.h"

void tttScanInit(BoardState &board) {
    for (int i = 0; i < 9; ++i) {
        board.cell[i] = BoardState::CELL_EMPTY;
    }
}

void tttScanBoard(BoardState &board, bool isUturn, float rd, float ld) {
    return;
}
