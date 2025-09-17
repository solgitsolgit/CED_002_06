int mic_analog_in = A0;
int RedPin = 3;
int GreenPin = 4;
int YellowPin = 5;
int sensorValue = 0;

void setup() {
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(YellowPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(mic_analog_in);

  if(sensorValue < 30) {
    digitalWrite(RedPin, HIGH);
  }
  else {
    digitalWrite(RedPin, LOW);
  }

  if(sensorValue > 30 && sensorValue < 60) {
    digitalWrite(GreenPin, HIGH);
  }
  else {
    digitalWrite(GreenPin, LOW);
  }

  if(sensorValue > 60) {
    digitalWrite(YellowPin, HIGH);
  }
  else {
    digitalWrite(YellowPin, LOW);
  }

  Serial.println(sensorValue, DEC);
  delay(200);
}

// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066
