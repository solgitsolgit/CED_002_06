#pragma once
// ===== Ultrasonic Controller (강신의) =====
#include <Arduino.h>
#include "constants.h"

void usInit();

float usReadLeftCm();

float usReadRightCm();