#include "ttt_solver.h"

static const uint16_t TTT_WIN_MASKS[8] = {
  0b000000111,
  0b000111000,
  0b111000000,
  0b001001001,
  0b010010010,
  0b100100100,
  0b100010001,
  0b001010100
};

static inline uint16_t tttBitOfPos(int pos1to9) {
  return (pos1to9 >= 1 && pos1to9 <= 9)
         ? (uint16_t)(1u << (pos1to9 - 1))
         : (uint16_t)0;
}

static bool tttIsWin(uint16_t mask) {
  for (int i = 0; i < 8; i++) {
    if ((mask & TTT_WIN_MASKS[i]) == TTT_WIN_MASKS[i]) {
      return true;
    }
  }
  return false;
}

int tttFindWinningMove(const BoardState& board,
                       const int myMoves[],
                       int myMoveCount)
{
  uint16_t myMask    = 0;
  uint16_t otherMask = 0;

  for (int i = 0; i < 9; i++) {
    if (board.cells[i] == BoardState::CELL_MINE) {
      myMask |= (uint16_t)(1u << i);
    } else if (board.cells[i] == BoardState::CELL_OTHER) {
      otherMask |= (uint16_t)(1u << i);
    }
  }

  for (int i = 0; i < myMoveCount; i++) {
    int pos = myMoves[i];
    if (pos < 1 || pos > 9) continue;
    myMask |= tttBitOfPos(pos);
  }

  otherMask &= ~myMask;

  uint16_t occMask = myMask | otherMask;

  for (int pos = 1; pos <= 9; pos++) {
    uint16_t b = tttBitOfPos(pos);
    if ((occMask & b) != 0) continue;
    uint16_t myNext = myMask | b;
    if (tttIsWin(myNext)) {
      return pos;
    }
  }

  for (int pos = 1; pos <= 9; pos++) {
    uint16_t b = tttBitOfPos(pos);
    if ((occMask & b) != 0) continue;
    uint16_t otherNext = otherMask | b;
    if (tttIsWin(otherNext)) {
      return pos;
    }
  }

  return -1;
}
