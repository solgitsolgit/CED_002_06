#pragma once
#include <Arduino.h>
#include "constants.h"

void InitHW();

int ReadPhotoSensor();

bool IsDark();

void LED_On();

void LED_Off();