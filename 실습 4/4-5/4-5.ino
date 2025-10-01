#include <ADXL345.h>
#include <Wire.h>

ADXL345 acc;

int sw = 3;
int buzzer = 4;
unsigned long start_time = 0, elapsed_time = 0;
boolean state = false;

double Xg, Yg, Zg;
double bXg = 0, bYg = 0, bZg = 0;
int count = 0, motion = 0;

void detectMotion() {
  motion = 1;
  delay(100);
}

void switchFn() {
  state = !state;
  elapsed_time = millis();
}

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
  Serial.begin(9600);
  acc.begin();

  attachInterrupt(0, detectMotion, RISING);
  attachInterrupt(1, switchFn, FALLING);
}

void loop() {
  if (digitalRead(3) == 0) {
    tone(buzzer, 300, 1000);
  }

  if (state == 1) {
    start_time = millis();

    acc.read(&Xg, &Yg, &Zg);
    bXg = Xg;
    bYg = Yg;
    bZg = Zg;

    if (motion == 1) {
      if ((bXg * bXg + bYg * bYg + bZg * bZg) > 0.00001) {
        count++;
        Serial.print("number of times : ");
        Serial.println(count);
      }
      motion = 0;
    }

    if ((start_time - elapsed_time) >= 30000) {
      count = 0;
      state = 0;
      tone(buzzer, 300, 1000);
    }
  }
}



// CED 002, group 06, 2020-14247 강신의
// CED 002, group 06, 2023-14669 임태현
// CED 002, group 06, 2025-17066 김정환