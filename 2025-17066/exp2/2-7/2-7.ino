const int ledPinRED = 13;
const int ledPinGREEN = 12;
int ledStateRED = 0;
int ledStateGREEN = 1;
unsigned long previousMillisRED = 0;
unsigned long previousMillisGREEN = 0;

void setup() {
  pinMode(ledPinRED, OUTPUT);
  pinMode(ledPinGREEN, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillisRED >= 1000)
  {
    previousMillisRED = currentMillis;
    ledStateRED = !ledStateRED;
  }

  if (currentMillis - previousMillisGREEN >= 1500)
  {
    previousMillisGREEN = currentMillis;
    ledStateGREEN = !ledStateGREEN;
  }
  digitalWrite(ledPinRED, ledStateRED);
  digitalWrite(ledPinGREEN, ledStateGREEN);
}

// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066