const int RED = 5;
const int YELLOW = 6;
const int GREEN = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
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

//group 6, 2023-14669
