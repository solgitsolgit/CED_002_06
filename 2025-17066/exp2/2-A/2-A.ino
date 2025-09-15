const int redLedPin = 6;
const int yellowLedPin = 5;
const int greenLedPin = 3;

const int rgbRedPin = 9;
const int rgbGreenPin = 10;
const int rgbBluePin = 11;

void setup() {
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(rgbRedPin, OUTPUT);
  pinMode(rgbGreenPin, OUTPUT);
  pinMode(rgbBluePin, OUTPUT);
}

void loop() {
  for (int brightness = 0; brightness <= 250; brightness += 10)
  {
    analogWrite(redLedPin, brightness);
    analogWrite(yellowLedPin, brightness);
    analogWrite(greenLedPin, brightness);
    analogWrite(rgbRedPin, brightness);
    analogWrite(rgbGreenPin, brightness);
    analogWrite(rgbBluePin, brightness);
    delay(1000);
  }
}

// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066
