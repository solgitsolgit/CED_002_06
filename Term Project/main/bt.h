#pragma once

#include <Arduino.h>
#include "constants.h"
#include "commons.h"
#include <stdio.h>  // snprintf

void btInit();

// 문자 기반 non-blocking 방식 명령 수신
Mode btPollCommand(int* outCount, int outMoves[], int outMax);

// '1'~'9' 입력 수신 (문자 하나)
// 숫자 수신 시 true 반환 + outCellIndex에 위치 저장 (1~9)
bool btReadMove(int* outCellIndex);

bool btReadNumbersLineBlocking(int& count, int outArr[], int maxLen);

void btFlushInput(unsigned long ms);