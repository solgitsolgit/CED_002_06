
#include <Arduino.h>
#include <Wire.h> // I2C
#include <LiquidCrystal_I2C.h> // LCD
#include <SoftwareSerial.h> // Bluetooth[]

#include "car_hw.h"

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

    pinMode(LED_PIN, OUTPUT); // LED Pin

    // Communication Initialization
    Serial.begin(9600); // PC Serial
}

// Read Photo Sensor
int ReadPhotoSensor() {
    return analogRead(PhotoSensor);
}

// Check if it's Dark
bool IsDark() {
    int sensorValue = ReadPhotoSensor();
    //Serial.print("Photo Sensor Value: ");
    //Serial.println(sensorValue);
    bool ret  =sensorValue < PhotoThreshold;
    //Serial.print(", IsDark:");
    //Serial.println(ret);
    //Serial.println("\n");
    return ret;
}