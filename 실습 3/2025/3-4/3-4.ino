const int ledPin = 13;
const int inputPin = 2;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
}

void loop() {
  int value = digitalRead(inputPin);

  if (value == HIGH) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
}

// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066