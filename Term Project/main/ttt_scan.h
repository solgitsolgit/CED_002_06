#pragma once

#include <Arduino.h>
#include "constants.h"
#include "commons.h"    

// 틱택토 탐색 시작 전 상태 초기화
void tttScanInit(BoardState &board);


//  - CELL_OTHER: 상대 말(종이컵) 있다고 판단
//  - CELL_EMPTY: 빈 칸
bool tttScanBoard(BoardState &board, bool isUturn, float rd, float ld);
