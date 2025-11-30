#include "line_sensor.h"

void lineSensorInit() {
    // 라인 센서 핀은 이미 constants.h에서 INPUT으로 설정됨
    // 추가 초기화가
}

uint8_t lineRead() {
    uint8_t value = 0;
    if (analogRead(LT_MODULE_L) > LT_THRESHOLD) {
        value |= 0x04; // 왼쪽 검정
    }
    if (analogRead(LT_MODULE_F) > LT_THRESHOLD) {
        value |= 0x02; // 중앙 검정
    }
    if (analogRead(LT_MODULE_R) > LT_THRESHOLD) {
        value |= 0x01; // 오른쪽 검정
    }
    return value;
}

bool lineIsIntersection(uint8_t lineValue) {
    return (lineValue & 0x07) == 0x07; // 3개 센서 모두 검정
}

bool lineIsCentered(uint8_t lineValue) {
    return (lineValue & 0x02) == 0x02; // 중앙 센서가 검정인지
}