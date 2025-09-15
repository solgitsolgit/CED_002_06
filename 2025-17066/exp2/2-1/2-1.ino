const int RED = 5;
const int YELLOW = 6;
const int GREEN = 7;

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loop() {
  digitalWrite(RED, 1);
  delay(1000);
  digitalWrite(YELLOW, 1);
  delay(1000);
  digitalWrite(GREEN, 1);
  delay(1000);
  digitalWrite(RED, 0);
  delay(1000);
  digitalWrite(YELLOW, 0);
  delay(1000);
  digitalWrite(GREEN, 0);
  delay(1000);
}

// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066
