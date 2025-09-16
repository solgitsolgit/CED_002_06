int redPin = 9;
int greenPin = 10;
int bluePin = 11;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void loop() {
  setColor(255, 0, 0);
  delay(2000);
  setColor(0, 255, 0);
  delay(2000);
  setColor(0, 0, 255);
  delay(2000);
  setColor(255, 255, 0);
  delay(2000);
  setColor(255, 0, 255);
  delay(2000);
  setColor(0, 255, 255);
  delay(2000);
  setColor(255, 255, 255);
  delay(2000);
  setColor(0, 0, 0);
  delay(2000);
}

// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066
