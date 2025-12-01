#pragma once

#include <Arduino.h>
#include "constants.h"
#include "motor.h"
#include "ultrasonic.h"
#include "line.h"      // lineRead(), lineIsIntersection() 같은 것 있다고 가정
#include "commons.h"    // BoardState, CELL_EMPTY, CELL_OTHER 등 정의

// 틱택토 탐색 시작 전 상태 초기화
void tttScanInit();

// 틱택토 보드 9칸을 탐색해서 board에 채운다.
//  - CELL_OTHER: 상대 말(종이컵) 있다고 판단
//  - CELL_EMPTY: 빈 칸
void tttScanBoard(BoardState &board);
