#include "bt.h"
#include <SoftwareSerial.h>
#include "constants.h"
#include "lcd.h"

// btSerial은 CarHW.ino에서 생성 & begin()까지 완료되어 있음.
// 여기서는 extern으로 가져와서 "읽기"만 한다.
SoftwareSerial btSerial(BT_RX, BT_TX);

void btInit() {
    btSerial.begin(9600); // Bluetooth
}

// 문자 기반 명령 수신
//  - 데이터가 없으면 BT_CMD_NONE
//  - 's' → STOP
//  - 'g' → START
Mode btPollCommand() {
    if (btSerial.available() > 0) {
        char c = btSerial.read();

        // 디버깅이 필요하면 PC 시리얼로 에코 가능:
        // Serial.print("[BT RX]: ");
        // Serial.println(c);

        if (c == '0') {
            lcdDisplayMessage("[BTRX] 0", " ");
            return MODE_LFS;
        }
        if (c == '1') {
            lcdDisplayMessage("[BTRX] 1", " ");
            return MODE_STOP;
        }
        if (c == '2') {
            lcdDisplayMessage("[BTRX] 2", " ");
            return MODE_SCAN;
        }
        if (c == '3') {
            lcdDisplayMessage("[BTRX] 3", " ");
            return MODE_TTT;
        }
        if (c == '4') {
            lcdDisplayMessage("[BTRX] 4", " ");
            return MODE_TTT_MAN;
        }
        Serial.print("[BT] Unknown command: ");
    }

    return MODE_NULL;
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

// ==============================
// BT 다중 숫자 입력 함수
// ==============================
bool btReadNumbersLineBlocking(int& count, int outArr[], int maxLen) {
    if (outArr == nullptr || maxLen <= 0) {
        count = 0;
        return false;
    }

    // 1) 한 줄을 받을 버퍼
    //    (너무 길게 받을 필요 없음: 최대 "9" + 숫자 9개 + 여분)
    char buf[32];
    int idx = 0;

    // 안내 표시 (원하면 제거 가능)
    lcdDisplayMessage("[BT] Input...", "Send: Nxxxxx");

    // 2) 줄바꿈이 들어올 때까지 blocking으로 읽기
    while (true) {
        // 데이터 올 때까지 대기
        while (btSerial.available() <= 0) { /* wait */ }

        char c = (char)btSerial.read();

        // 줄바꿈이면 입력 종료
        if (c == '\n' || c == '\r') {
            break;
        }

        // 공백/탭은 무시
        if (c == ' ' || c == '\t') continue;

        // 버퍼에 저장 (오버플로 방지)
        if (idx < (int)sizeof(buf) - 1) {
            buf[idx++] = c;
        }
    }
    buf[idx] = '\0';

    // 3) 파싱: 첫 글자는 "개수"
    if (idx <= 0 || buf[0] < '0' || buf[0] > '9') {
        count = 0;
        lcdDisplayMessage("[BT] ERR", "Bad format");
        return false;
    }

    int expected = buf[0] - '0';
    if (expected > maxLen) expected = maxLen;

    // 4) 뒤에서 숫자(1~9)를 expected개 만큼 읽기
    int got = 0;
    for (int i = 1; buf[i] != '\0' && got < expected; i++) {
        char c = buf[i];
        if (c >= '1' && c <= '9') {
            outArr[got++] = c - '0';
        }
        // 그 외 문자는 무시 (예: 쉼표 등)
    }

    // 5) 결과 처리
    if (got != expected) {
        // 입력이 모자랐다면: (정책 1) 실패로 처리
        // 또는 (정책 2) got만큼으로 count를 줄여서 진행 가능
        // 여기서는 안전하게 "실패"로 하고 다시 입력받게 하는 걸 추천.
        count = got;
        char line2[17];
        snprintf(line2, sizeof(line2), "need %d got %d", expected, got);
        lcdDisplayMessage("[BT] ERR", line2);
        return false;
    }

    count = expected;

    // LCD 확인 표시
    char line2[17];
    snprintf(line2, sizeof(line2), "OK cnt=%d", count);
    lcdDisplayMessage("[BT] DONE", line2);

    return true;
}