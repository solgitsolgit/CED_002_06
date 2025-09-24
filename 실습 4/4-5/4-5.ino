#include <ADXL345.h>
#include <Wire.h>

ADXL345 acc;


//변수선언
int sw = 3;
int buzzer = 4;
unsigned long start_time = 0, elapsed_time = 0;
boolean state = false;

double Xg, Yg, Zg;
double bXg = 0, bYg = 0, bZg = 0;
int count = 0, motion = 0;


//가속도 센서가 측정값에 변화를 받아들였을 때 인터럽트 발생
void detectMotion() {
  motion = 1;
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


//인터럽트 발생 시 Xg Yg Zg 측정하여 저장
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
      if ((bXg * bXg + bYg * bYg + bZg * bZg) > 1000) {
        count++;
        Serial.print("number of steps : ");
        Serial.println(count);
      }
      motion = 0;
    }

    if ((start_time - elapsed_time) >= 30000) {
      count = 0;  //숫자 리셋
      state = 0;
      tone(buzzer, 300, 1000);
    }
  }
}