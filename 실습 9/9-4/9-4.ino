#define TRIG_PIN 12
#define ECHO_PIN 13

int speed = 200;
long last_cm = 10;

#define ENA 6
#define EN1 7
#define EN2 3
#define EN3 4
#define EN4 2
#define ENB 5

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(ENA, OUTPUT); // ENA
  pinMode(EN1, OUTPUT); // EN1
  pinMode(EN2, OUTPUT); // EN2
  pinMode(ENB, OUTPUT); // ENB
  pinMode(EN3, OUTPUT); // EN3
  pinMode(EN4, OUTPUT); // EN4

}

long microsecondsToCentimeters(long microseconds) {
  return microseconds/29/2;

}

void goForward() {
  digitalWrite(EN1, HIGH);
  digitalWrite(EN2, LOW);
  analogWrite(ENA, speed);
  digitalWrite(EN3, HIGH);
  digitalWrite(EN4, LOW);
  analogWrite(ENB, speed);
}

void goBackward() {
  digitalWrite(EN1, LOW);
  digitalWrite(EN2, HIGH);
  analogWrite(ENA, speed);
  digitalWrite(EN3, LOW);
  digitalWrite(EN4, HIGH);
  analogWrite(ENB, speed);
}

void loop() {
  long duration, cm;
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);

  cm = microsecondsToCentimeters(duration);

  if (cm == 0 or cm > 100) {
    cm = last_cm;
  } else {
    last_cm = cm;
  }

  if (cm <= 10) {          // 바로 20 사용
    goBackward();
    delay(400);            // 잠깐 후진
  } 
  else {
    goForward();
    }

  Serial.println(cm);
}
