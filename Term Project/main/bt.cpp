#include "bt.h"
#include <SoftwareSerial.h>
#include "constants.h"

// btSerial은 CarHW.ino에서 생성 & begin()까지 완료되어 있음.
// 여기서는 extern으로 가져와서 "읽기"만 한다.
extern SoftwareSerial btSerial;

void btInit() {
    // 별도의 초기화는 필요 없음 (InitHW()에서 이미 처리)
    // 혹시 남아있는 버퍼 비우고 시작하고 싶다면:
    while (btSerial.available() > 0) {
        btSerial.read();
    }
}

// 문자 기반 명령 수신
//  - 데이터가 없으면 BT_CMD_NONE
//  - 's' → STOP
//  - 'g' → START
BtCommand btPollCommand() {
    if (btSerial.available() > 0) {
        char c = btSerial.read();

        // 디버깅이 필요하면 PC 시리얼로 에코 가능:
        // Serial.print("[BT RX]: ");
        // Serial.println(c);

        if (c == 's') {
            return BT_CMD_STOP;
        }
        if (c == 'g') {
            return BT_CMD_START;
        }
        // 그 외 문자는 지금은 무시
    }

    return BT_CMD_NONE;
}

// 틱택토 위치 수신 (숫자 하나)
//  - '1' ~ '9' 문자 들어오면 true + outCellIndex에 1~9 저장
//  - 그 외/없으면 false
bool btReadMove(int* outCellIndex) {
    if (outCellIndex == nullptr) return false;

    if (btSerial.available() > 0) {
        char c = btSerial.read();

        if (c >= '1' && c <= '9') {
            *outCellIndex = c - '0';  // 문자 → 정수
            return true;
        }
        // 숫자가 아니면 무시
    }

    return false;
}
