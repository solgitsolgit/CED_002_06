#pragma once
#include <Arduino.h>
#include "constants.h"

void InitHW();

// Read Photo Sensor
int ReadPhotoSensor();

// Check if it's Dark
bool IsDark();

void LED_On();

void LED_Off();