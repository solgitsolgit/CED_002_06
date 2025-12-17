#pragma once
#include <Arduino.h>
#include "commons.h"   // BoardState 정의 있는 곳
#include "lcd.h"      // lcdPrintAnswer()

// myMoves는 1~9 인덱스들이 들어있는 배열.
// myMoveCount로 실제 개수 전달.
int runTicTacToe(const BoardState& board,
                 const int myMoves[],
                 int myMoveCount);

int solveTTT(BoardState& board, int myMoves[], int myMoveCount);