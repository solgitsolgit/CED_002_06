#include "bt.h"
#include <SoftwareSerial.h>

// SoftwareSerial(RX, TX)
static SoftwareSerial btSerial(BT_RX, BT_TX);

void btInit() {
    btSerial.begin(9600);  // HC-05 기본 속도
}

// 문자 기반 명령 수신
BtCommand btPollCommand() {
    if (btSerial.available() > 0) {
        char c = btSerial.read();

        // STOP 명령: 's'
        if (c == 's') {
            return BT_CMD_STOP;
        }

        // START 명령: 'g' (go)
        if (c == 'g') {
            return BT_CMD_START;
        }
    }

    return BT_CMD_NONE;
}

// 틱택토 위치 수신 (숫자 하나)
bool btReadMove(int* outCellIndex) {
    if (outCellIndex == nullptr) return false;

    if (btSerial.available() > 0) {
        char c = btSerial.read();

        if (c >= '1' && c <= '9') {
            *outCellIndex = c - '0';  // 문자 → 정수 변환
            return true;
        }
    }

    return false;
}
