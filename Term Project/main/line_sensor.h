#pragma once
#include <Arduino.h>
#include "constants.h"

// ===== Line Sensor (김정환) =====

// 라인 센서 핀 설정, threshold 설정 등
void lineSensorInit();

// 라인 상태 읽기
// 반환값: 비트 OR 조합
// - 왼쪽 검정:  LINE_LEFT   (0x04)
// - 중앙 검정:  LINE_CENTER (0x02)
// - 오른쪽 검정: LINE_RIGHT  (0x01)
// 예: 중앙만 검정 → 0x02, 왼+오 → 0x05
uint8_t lineRead();

// 교차점(3개 센서 모두 검정)인지 판단
bool lineIsIntersection(uint8_t lineValue);

// "라인 위에 제대로 올라와 있다" 정도의 체크 (원하면 추가용)
bool lineIsCentered(uint8_t lineValue);  // 중앙 센서가 검정인지 등