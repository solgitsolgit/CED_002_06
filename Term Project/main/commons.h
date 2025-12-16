#pragma once
#include <stdint.h>

enum CellState { CELL_EMPTY = 0, CELL_MINE = 1, CELL_OTHER = 2 };
struct BoardState {
    enum CellState {
        CELL_EMPTY = 0,
        CELL_MINE = 1,
        CELL_OTHER = 2
    };
    uint8_t cell[9] = {};
};

enum Mode {
  MODE_NULL = -1,
  MODE_LFS = 0,      // Left-First-Search 라인트레이싱 모드
  MODE_STOP, // 1
  MODE_SCAN, // 2
  MODE_TTT, // 3
  MODE_TTT_MAN // 4, Manual Mode
};