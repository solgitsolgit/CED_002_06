//변수선언
int mic_analog_in = A0;
int LED3_pin = 3;
int LED4_pin = 4;
int LED5_pin = 5;
int sensorValue = 0;

//각 핀 및 보드레이트 설정
void setup() {
  pinMode(LED3_pin, OUTPUT);
  pinMode(LED4_pin, OUTPUT);
  pinMode(LED5_pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  sensorValue = analogRead(mic_analog_in);

  //각 센서 값에 따라 출력값 결정
  if(sensorValue < 30) {
    digitalWrite(LED3_pin, HIGH);
  } else {
    digitalWrite(LED3_pin, LOW);
  }

  if(sensorValue > 30 && sensorValue < 60) {
    digitalWrite(LED4_pin, HIGH);
  } else {
    digitalWrite(LED4_pin, LOW);
  }

  if(sensorValue > 60) {
    digitalWrite(LED5_pin, HIGH);
  } else {
    digitalWrite(LED5_pin, LOW);
  }

  Serial.println(sensorValue, DEC);
  delay(200);
}

// group 6, 2020-14247 강신의, 2023-14669 임태현, 2025-17066 김정환