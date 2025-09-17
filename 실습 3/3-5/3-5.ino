int lightPin = 10;
int ledPin = 11;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  Serial.println(digitalRead(lightPin));

  if (digitalRead(lightPin) == 1) {
    digitalWrite(ledPin, 1);
  }
  else {
    digitalWrite(ledPin, 0);
  }

  delay(10);
}

// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066