#pragma once
#include <stdint.h>

enum CellState { CELL_EMPTY = 0, CELL_MINE = 1, CELL_OTHER = 2 };
struct BoardState {
    enum CellState {
        CELL_EMPTY = 0,
        CELL_MINE = 1,
        CELL_OTHER = 2
    };
    uint8_t cell[9];
};