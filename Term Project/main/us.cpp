#include "us.h"
#include "constants.h"
#include <Arduino.h>

// 내부에서만 쓰는 helper 함수들
namespace {
    // 거리 변환 함수 (기존 예제 그대로)
    float microsecondsToCentimeters(long microseconds) {
        // 소리 속도: 약 29us/cm (왕복이라 2로 나눔)
        return microseconds / 29.0f / 2.0f;
    }

    // 실제 측정 함수: 특정 trig/echo 핀 쌍에 대해 거리(cm) 측정
    float measureDistanceCm(int trigPin, int echoPin) {
        // Trig 핀 안정화
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);

        // Trig 핀 HIGH 10us → 초음파 발사
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);

        // Echo 핀이 HIGH인 구간의 길이 측정
        long duration = pulseIn(echoPin, HIGH);

        // duration == 0 (타임아웃 비슷한 상황)이면 -1 반환
        if (duration == 0) {
            return -1.0f;
        }

        return microsecondsToCentimeters(duration);
    }
}

// ------------------- 공개 함수 구현 -------------------

void usInit() {
    // InitHW()에서 이미 pinMode 설정을 해주고 있으므로
    // 여기서 따로 할 일은 없다.
    // 필요하다면 안전하게 LOW로 한 번 초기화만 해도 됨.
    digitalWrite(L_Trig, LOW);
    digitalWrite(R_Trig, LOW);
}

float usReadLeftCm() {
    return measureDistanceCm(L_Trig, L_Echo);
}

float usReadRightCm() {
    return measureDistanceCm(R_Trig, R_Echo);
}
