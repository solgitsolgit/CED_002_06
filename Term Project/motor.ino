#include <Arduino.h>
#include "constants.h"
#include "motor.h"

int currentSpeed = 200;

// Set Speed
void SetSpeed(int speed) {
    if (speed > 255) currentSpeed = 255;
    else if (speed < 0) currentSpeed = 0;
    else currentSpeed = speed;
}

// Move Forward
void MoveFront() {
    digitalWrite(EN1, HIGH);
    digitalWrite(EN2, LOW);
    analogWrite(ENA, currentSpeed);
    digitalWrite(EN3, HIGH);
    digitalWrite(EN4, LOW);
    analogWrite(ENB, currentSpeed);
}

// Move Backward
void MoveBack() {
    digitalWrite(EN1, LOW);
    digitalWrite(EN2, HIGH);
    analogWrite(ENA, currentSpeed);
    digitalWrite(EN3, LOW);
    digitalWrite(EN4, HIGH);
    analogWrite(ENB, currentSpeed);
}

// Turn Left
void TurnLeft() {
    digitalWrite(EN1, LOW);
    digitalWrite(EN2, HIGH);
    analogWrite(ENA, currentSpeed);
    digitalWrite(EN3, HIGH);
    digitalWrite(EN4, LOW);
    analogWrite(ENB, currentSpeed);
}

// Turn Right
void TurnRight() {
    digitalWrite(EN1, HIGH);
    digitalWrite(EN2, LOW);
    analogWrite(ENA, currentSpeed);
    digitalWrite(EN3, LOW);
    digitalWrite(EN4, HIGH);
    analogWrite(ENB, currentSpeed);
}

// Stop
void StopCar() {
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
    digitalWrite(EN1, LOW);
    digitalWrite(EN2, LOW);
    digitalWrite(EN3, LOW);
    digitalWrite(EN4, LOW);
}