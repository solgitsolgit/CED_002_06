#pragma once

#include <Arduino.h>
#include "constants.h"
#include "commons.h"
#include <stdio.h>

void btInit();

Mode btPollCommand(int* outCount, int outMoves[], int outMax);

bool btReadMove(int* outCellIndex);

bool btReadNumbersLineBlocking(int& count, int outArr[], int maxLen);

void btFlushInput(unsigned long ms);