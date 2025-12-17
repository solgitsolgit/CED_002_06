#pragma once
#include <Arduino.h>
#include "constants.h"

// ===== Line Sensor (김정환) =====

void lineSensorInit();

uint8_t lineRead();


bool lineIsIntersection(uint8_t lineValue);

bool lineIsCentered(uint8_t lineValue); 