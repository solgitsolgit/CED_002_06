#pragma once
// ===== Ultrasonic Controller (강신의) =====
#include <Arduino.h>
#include "constants.h"

// 초음파 센서 핀 초기화 (좌/우 2개)
void usInit();

// 왼쪽 초음파 센서에서 거리(cm)를 읽음
// 측정 실패 시 음수 값(-1 등)을 반환하는 식으로 설계해도 됨
float usReadLeftCm();

// 오른쪽 초음파 센서에서 거리(cm)를 읽음
float usReadRightCm();
// ===== End of Ultrasonic Controller =====