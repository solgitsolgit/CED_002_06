const int ledPin = 13;
volatile byte ledState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  TIMSK2 = 0x01;
  TCCR2B = 0x07;
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPin, ledState);
}

ISR(TIMER2_OVF_vect) {
  ledState = !ledState;
}

//group 6 2023-14669