const int ledPinRED = 13;
const int ledPinGREEN = 12;
int ledStateRED = 0;
int ledStateGREEN = 0;
unsigned long previousMillisRED = 0;
unsigned long previousMillisGREEN = 0;

void setup() {
  pinMode(ledPinRED, OUTPUT);
  pinMode(ledPinGREEN, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillisRED >= 1000) {
    previousMillisRED = currentMillis;
    ledStateRED = !ledStateRED;
    digitalWrite(ledPinRED, ledStateRED);
  }

  if (currentMillis - previousMillisRED >= 500) {
    ledStateGREEN = ledStateRED;
    digitalWrite(ledPinGREEN, ledStateGREEN);
  } 
}

// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066