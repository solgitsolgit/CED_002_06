
#include <Arduino.h>
#include <Wire.h> // I2C
#include <LiquidCrystal_I2C.h> // LCD
#include <SoftwareSerial.h> // Bluetooth[]

#include "car_hw.h"

SoftwareSerial btSerial(BT_RX, BT_TX);

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

void InitHW() {
    // Motor Pin
    pinMode(ENA, OUTPUT);
    pinMode(EN1, OUTPUT);
    pinMode(EN2, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(EN3, OUTPUT);
    pinMode(EN4, OUTPUT);

    // Line Tracer Pin
    pinMode(LT_MODULE_L, INPUT);
    pinMode(LT_MODULE_F, INPUT);
    pinMode(LT_MODULE_R, INPUT);

    // Ultrasonic Sensor Pin
    pinMode(L_Trig, OUTPUT);
    pinMode(L_Echo, INPUT);
    pinMode(R_Trig, OUTPUT);
    pinMode(R_Echo, INPUT);

    // Photo Sensor Pin
    pinMode(PhotoSensor, INPUT);

    // Communication Initialization
    Serial.begin(9600); // PC Serial
    btSerial.begin(9600); // Bluetooth

    // LCD
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("System Ready");
}