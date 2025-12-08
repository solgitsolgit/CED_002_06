#ifndef CarHW
#define CarHW

#include <Arduino.h>
#include <Wire.h> // I2C
#include <LiquidCrystal_I2C.h> // LCD
#include <SoftwareSerial.h> // Bluetooth

// Motor Driver
#define ENA 6 // Left Motor
#define EN1 7
#define EN2 3
#define ENB 5 // Right Motor
#define EN3 4
#define EN4 2
int currentSpeed = 200;

// Line Tracer
#define LT_MODULE_L A2
#define LT_MODULE_F A1
#define LT_MODULE_R A0
#define LT_THRESHOLD 200

// Ultrasonic Sensor
#define L_Trig 10
#define L_Echo 11
#define R_Trig 12
#define R_Echo 13

// Photo Sensor
#define PhotoSensor A3
#define PhotoThreshold 300

// Bluetooth
#define BT_RX 8
#define BT_TX 9
SoftwareSerial btSerial(BT_RX, BT_TX);

// LCD (SDA, SCL)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// LED
#define LED_PIN A2

// Hardware Initialization
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
    
    // LED
    pinMode(LED_PIN, OUTPUT);
}

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

// Read Line Tracer Sensors
void IsLT(bool &left, bool &front, bool &right) {
    left  = (analogRead(LT_MODULE_L) > LT_THRESHOLD);
    front = (analogRead(LT_MODULE_F) > LT_THRESHOLD);
    right = (analogRead(LT_MODULE_R) > LT_THRESHOLD);
}

// Measure Distance with Ultrasonic Sensor
long ReadDistance(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 20000); // Timeout
    if (duration == 0) return 999; // Out of range
    return duration * 0.034 / 2; // Distance in cm
}

// Measure Left Distance
long GetLeftDistance() {
    return ReadDistance(L_Trig, L_Echo);
}

// Measure Right Distance
long GetRightDistance() {
    return ReadDistance(R_Trig, R_Echo);
}

// Read Photo Sensor
int ReadPhotoSensor() {
    return analogRead(PhotoSensor);
}

// Check if it's Dark
bool IsDark() {
    return ReadPhotoSensor() < PhotoThreshold;
}

// Bluetooth
char GetBT() {
    if (btSerial.available()) {
        return (char)btSerial.read();
    }
    return 0;
}

// Display on LCD
void DisplayLCD(const String &line1, const String &line2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line1);
    lcd.setCursor(0, 1);
    lcd.print(line2);
}

#endif