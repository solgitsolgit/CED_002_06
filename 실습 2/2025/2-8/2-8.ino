const int ledPin = 13;
volatile byte ledState = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  TIMSK2 |= 0x01;
  TCCR2B = 0x07;
}

void loop() {
  digitalWrite(ledPin, ledState);
}

ISR(TIMER2_OVF_vect)
{
  ledState = !ledState;
}

// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066
