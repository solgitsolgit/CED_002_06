#include "us.h"

// 내부에서만 쓰는 helper 함수들
namespace {
    // 타임아웃 (마이크로초). 약 30ms = 약 5m 정도까지 측정.
    const unsigned long US_TIMEOUT = 30000UL;

    // 거리 변환 함수 (네가 쓰던 식 그대로)
    float microsecondsToCentimeters(long microseconds) {
        // 소리 속도: 약 29us/cm (왕복이라 2로 나눔)
        return microseconds / 29.0f / 2.0f;
    }

    // 실제 측정 함수: 특정 trig/echo 핀 쌍에 대해 거리(cm) 측정
    float measureDistanceCm(int trigPin, int echoPin) {
        // 트리거 핀 안정화
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);

        // Trig 핀 HIGH 10us → 초음파 발사
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);

        // Echo 핀이 HIGH인 구간의 길이 측정 (타임아웃 포함)
        long duration = pulseIn(echoPin, HIGH, US_TIMEOUT);

        // 타임아웃 또는 이상 값 처리
        if (duration == 0) {
            return -1.0f;    // 측정 실패 시 음수 반환
        }

        return microsecondsToCentimeters(duration);
    }
}

// ------------------- 공개 함수 구현 -------------------

void usInit() {
    // 왼쪽 센서 핀 설정
    pinMode(L_Trig, OUTPUT);
    pinMode(L_Echo, INPUT);
    digitalWrite(L_Trig, LOW); // 초기 상태는 LOW

    // 오른쪽 센서 핀 설정
    pinMode(R_Trig, OUTPUT);
    pinMode(R_Echo, INPUT);
    digitalWrite(R_Trig, LOW);
}

float usReadLeftCm() {
    return measureDistanceCm(L_Trig, L_Echo);
}

float usReadRightCm() {
    return measureDistanceCm(R_Trig, R_Echo);
}
