#pragma once

#include <Arduino.h>
#include "constants.h"

void SetSpeed(int speed);
void MoveFront();
void MoveBack();
void TurnLeft();
void TurnRight();
void StopCar();

// 제자리 회전
void motorTurnLeftRaw(int speed);   // 왼쪽으로 회전
void motorTurnRightRaw(int speed);  // 오른쪽으로 회전

// "대략" 90도 / 180도 회전 (시간 기반으로) – 실험하면서 튜닝
void motorTurnLeft90();
void motorTurnRight90();
void motorTurnAround180();