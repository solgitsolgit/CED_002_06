#pragma once
#include <Arduino.h>
#include "commons.h"   
#include "lcd.h"   


int runTicTacToe(const BoardState& board,
                 const int myMoves[],
                 int myMoveCount);

int solveTTT(BoardState& board, int myMoves[], int myMoveCount);