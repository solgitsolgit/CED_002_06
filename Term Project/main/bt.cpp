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

static const unsigned long BT_LINE_TIMEOUT_MS = 3000; // 3초 타임아웃(필요시 조정)

// 한 줄 읽기: \n 또는 \r에서 종료. 공백은 유지/제거 선택 가능.
// 반환: true면 buf에 한 줄 완성, false면 타임아웃/실패
static bool btReadLine(char* buf, int bufSize) {
    if (buf == nullptr || bufSize <= 1) return false;

    int idx = 0;
    unsigned long start = millis();

    while (true) {
        // 타임아웃
        if (millis() - start > BT_LINE_TIMEOUT_MS) {
            buf[0] = '\0';
            return false;
        }

        if (btSerial.available() <= 0) {
            delay(1);
            continue;
        }

        char c = (char)btSerial.read();

        // 줄 종료
        if (c == '\n' || c == '\r') {
            break;
        }

        // (선택) 공백/탭 무시
        if (c == ' ' || c == '\t') continue;

        if (idx < bufSize - 1) {
            buf[idx++] = c;
        }
    }

    buf[idx] = '\0';
    return (idx > 0);
}

void btFlushInput(unsigned long ms) {
    unsigned long start = millis();
    while (millis() - start < ms) {
        while (btSerial.available() > 0) btSerial.read();
        delay(1);
    }
}

// 입력 포맷(권장):
// 0\n  -> MODE_LFS
// 1\n  -> MODE_STOP
// 2\n  -> MODE_SCAN
// 4\n  -> MODE_TTT_MAN
//
// 3|N|a1|a2|...|aN\n  -> MODE_TTT + outCount/outMoves 채움
// 예: 3|4|1|2|5|7\n
Mode btPollCommand(int* outCount, int outMoves[], int outMax) {
    if (btSerial.available() <= 0) return MODE_NULL;

    char line[64];
    if (!btReadLine(line, sizeof(line))) {
        return MODE_NULL;
    }

    char modeChar = line[0];

    // ---- 단순 모드 ----
    if (modeChar == '0') { lcdDisplayMessage("[BTRX] 0", " "); return MODE_LFS; }
    if (modeChar == '1') { lcdDisplayMessage("[BTRX] 1", " "); return MODE_STOP; }
    if (modeChar == '2') { lcdDisplayMessage("[BTRX] 2", " "); return MODE_SCAN; }

    // =========================================================
    // MODE_TTT (3): 3|N|a1|a2|...
    // =========================================================
    if (modeChar == '3') {
        lcdDisplayMessage("[BTRX] 3", "TTT data");

        if (outCount) *outCount = 0;
        if (outMoves && outMax > 0) {
            for (int i = 0; i < outMax; i++) outMoves[i] = 0;
        }

        char tmp[64];
        strncpy(tmp, line, sizeof(tmp));
        tmp[sizeof(tmp) - 1] = '\0';

        char* saveptr = nullptr;
        char* tok = strtok_r(tmp, "|", &saveptr); // "3"
        if (!tok) return MODE_TTT;

        tok = strtok_r(nullptr, "|", &saveptr);   // N
        if (!tok) return MODE_TTT;

        int N = atoi(tok);
        if (N < 0) N = 0;
        if (N > outMax) N = outMax;

        int got = 0;
        while (got < N) {
            tok = strtok_r(nullptr, "|", &saveptr);
            if (!tok) break;

            int v = atoi(tok);
            if (v >= 1 && v <= 9) {
                outMoves[got++] = v;
            }
        }

        if (outCount) *outCount = got;

        char l2[17];
        snprintf(l2, sizeof(l2), "N=%d got=%d", N, got);
        lcdDisplayMessage("TTT RX", l2);

        return MODE_TTT;
    }

    // =========================================================
    // MODE_TTT_MAN (4): 4|012102200  (9 chars: 0/1/2)
    // =========================================================
    if (modeChar == '4') {
        lcdDisplayMessage("[BTRX] 4", "TTT MAN");

        if (!outMoves || outMax < 9) {
            if (outCount) *outCount = 0;
            return MODE_TTT_MAN;
        }

        // line 예: "4|012102200" 또는 "4012102200"
        const char* p = line + 1;
        if (*p == '|') p++;   // '|' 있으면 스킵

        int got = 0;
        while (*p && got < 9) {
            if (*p == '0' || *p == '1' || *p == '2') {
                outMoves[got++] = *p - '0';
            }
            p++;
        }

        if (outCount) *outCount = got;

        // LCD 표시
        char l2[17];
        snprintf(l2, sizeof(l2), "cells=%d", got);
        lcdDisplayMessage("TTT MAN RX", l2);

        return MODE_TTT_MAN;
    }

    // ---- 알 수 없는 입력 ----
    Serial.print("[BT] Unknown line: ");
    Serial.println(line);
    return MODE_NULL;
}
