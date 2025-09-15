#include <IRremote.h>
const int receiverPin = 8;
IRrecv irrecv(receiverPin);
decode_results results;

const int RED = 7;
const int YELLOW = 6;
const int GREEN = 5;

boolean stateRED = false;
boolean stateYELLOW = false;
boolean stateGREEN = false;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void translateIR()
{
  switch (results.value)
  {
    case 0xFF30CF: stateRED = !stateRED;
    digitalWrite(RED, stateRED);
    break;
    case 0xFF18E7: stateYELLOW = !stateYELLOW;
    digitalWrite(YELLOW, stateYELLOW);
    break;
    case 0xFF7A85: stateGREEN = !stateGREEN;
    digitalWrite(GREEN, stateGREEN);
    break;
    case 0xFF10EF: 
    stateRED = stateYELLOW = stateGREEN = false;
    digitalWrite(RED, stateRED);
    digitalWrite(YELLOW, stateYELLOW);
    digitalWrite(GREEN, stateGREEN);
    break;
  }
}

void loop() {
  if (irrecv.decode(&results)) {
    translateIR();
    Serial.println(results.value, HEX);
    delay(300);
    irrecv.resume();
  }
}

// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066
