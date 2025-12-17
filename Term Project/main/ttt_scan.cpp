#include "ttt_scan.h"

static const float PIECE_MIN_CM_L = 16.0f;
static const float PIECE_MAX_CM_L = 22.0f;
static const float PIECE_MIN_CM_R = 16.0f;
static const float PIECE_MAX_CM_R = 22.0f;

static const float ULTRA_VALID_MIN_CM = 5.f;   // TUNE (필요시)
static const float ULTRA_VALID_MAX_CM = 200.0f; // TUNE (필요시)

static const uint16_t CELL5_OFFSET_MS = 250; // TUNE
static const uint16_t CELL5_WINDOW_MS = 500; // TUNE

static const int8_t LUT_L[8] = { -1, 9, 8, 7, 4, 1, 2, 3 }; // TUNE
static const int8_t LUT_R[8] = { -1, 8, 7, 4, 1, 2, 3, 6 }; // TUNE

static uint8_t  s_uturnCnt     = 0;
static bool     s_prevIsUturn  = false;
static uint32_t s_phaseStartMs = 0;

static inline bool isValidDist(float d) {
  return (d >= ULTRA_VALID_MIN_CM && d <= ULTRA_VALID_MAX_CM);
}

static inline bool isPieceInWindow(float d, float mn, float mx) {
  return isValidDist(d) && (d >= mn) && (d <= mx);
}

static inline void markOccupied(BoardState &board, int cellIdx0) {
  if (cellIdx0 < 0 || cellIdx0 >= 9) return;
  if (board.cell[cellIdx0] == BoardState::CELL_EMPTY) board.cell[cellIdx0] = BoardState::CELL_OTHER;
}

static void scanAtUturn(BoardState &board, uint8_t uturnCnt, float ld, float rd) {
  if (uturnCnt > 7) return;

  const int leftCell  = LUT_L[uturnCnt];
  const int rightCell = LUT_R[uturnCnt];

  if (leftCell >= 1 && leftCell <= 9) {
    if (isPieceInWindow(ld, PIECE_MIN_CM_L, PIECE_MAX_CM_L)) markOccupied(board, leftCell - 1);
  }
  if (rightCell >= 1 && rightCell <= 9) {
    if (isPieceInWindow(rd, PIECE_MIN_CM_R, PIECE_MAX_CM_R)) markOccupied(board, rightCell - 1);
  }
}

void tttScanInit(BoardState &board) {
  for (int i = 0; i < 9; ++i) board.cell[i] = BoardState::CELL_EMPTY;
  s_uturnCnt = 0;
  s_prevIsUturn = false;
  s_phaseStartMs = millis();
}

uint8_t tttScanGetUturnCount() {
  return s_uturnCnt;
}

bool tttScanBoard(BoardState &board, bool isUturn, float ld, float rd) {
  const bool rising = (isUturn && !s_prevIsUturn);
  s_prevIsUturn = isUturn;

  if (rising) {
    if (s_uturnCnt < 7) s_uturnCnt++;
    s_phaseStartMs = millis();
    scanAtUturn(board, s_uturnCnt, ld, rd);
  }

  if (s_uturnCnt == 5) {
    const uint32_t dt = millis() - s_phaseStartMs;
    if (dt >= CELL5_OFFSET_MS && dt <= (uint32_t)CELL5_OFFSET_MS + CELL5_WINDOW_MS) {
      if (isPieceInWindow(rd, PIECE_MIN_CM_R, PIECE_MAX_CM_R)) markOccupied(board, 4);
    }
  }
}
