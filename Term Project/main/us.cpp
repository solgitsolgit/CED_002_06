#include "us.h"
#include "constants.h"
#include <Arduino.h>

namespace {
    float microsecondsToCentimeters(long microseconds) {
        return microseconds / 29.0f / 2.0f;
    }

    float measureDistanceCm(int trigPin, int echoPin) {
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);

        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);

        long duration = pulseIn(echoPin, HIGH);

        if (duration == 0) {
            return -1.0f;
        }

        return microsecondsToCentimeters(duration);
    }
}


void usInit() {
    digitalWrite(L_Trig, LOW);
    digitalWrite(R_Trig, LOW);
}

float usReadLeftCm() {
    return measureDistanceCm(L_Trig, L_Echo);
}

float usReadRightCm() {
    return measureDistanceCm(R_Trig, R_Echo);
}
