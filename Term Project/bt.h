#pragma once

#include <Arduino.h>
#include "constants.h"

enum BtCommand {
  BT_CMD_NONE = 0,
  BT_CMD_STOP,
  BT_CMD_START
};

void btInit();

// 문자 기반 non-blocking 방식 명령 수신
BtCommand btPollCommand();

// '1'~'9' 입력 수신 (문자 하나)
// 숫자 수신 시 true 반환 + outCellIndex에 위치 저장 (1~9)
bool btReadMove(int* outCellIndex);
