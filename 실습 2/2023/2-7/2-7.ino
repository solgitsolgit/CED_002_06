const int ledPinRED = 13;
const int ledPinGREEN = 12;
int ledStateRED = 0;
int ledStateGREEN = 1;

unsigned long previousMillisRED = 0;
unsigned long previousMillisGREEN = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPinRED, OUTPUT);
  pinMode(ledPinGREEN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillisRED >= 1000)
  {
    previousMillisRED = currentMillis;
    ledStateRED = !ledStateRED;
  }

  if(currentMillis - previousMillisGREEN >= 1500)
  {
    previousMillisGREEN = currentMillis;
    ledStateGREEN = !ledStateGREEN;
  }
  digitalWrite(ledPinRED, ledStateRED);
  digitalWrite(ledPinGREEN, ledStateGREEN);
}

//group 6 2023-14669