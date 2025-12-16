#pragma once

#include <Arduino.h>

// Motor Driver
const int ENA = 6; // Left Motor
const int EN1 = 7;
const int EN2 = 3;
const int ENB = 5; // Right Motor
const int EN3 = 4;
const int EN4 = 2;
extern int currentSpeed;

// Line Tracer
const int LT_MODULE_L = A2;
const int LT_MODULE_F = A1;
const int LT_MODULE_R = A0;
const int LT_THRESHOLD = 200;

// Ultrasonic Sensor
const int L_Trig = 10;
const int L_Echo = 11;
const int R_Trig = 12;
const int R_Echo = 13;

// Photo Sensor
const int PhotoSensor = A3;
const int PhotoThreshold = 300;

// Bluetooth
const int BT_RX = 8;
const int BT_TX = 9;

#define LED_PIN A2