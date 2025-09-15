const int RED = 5;
int i =1;

void setup() {
  Serial.begin(9600);
  pinMode(RED, OUTPUT);
}

void loop() {
  if (i<20)
  {
    digitalWrite(RED, 1);
    delay(100-5*i);
    digitalWrite(RED, 0);
    delay(100-5*i);
    i=i+1;
  }
  else
  {
    digitalWrite(RED, 1);
    delay(1);
    digitalWrite(RED, 0);
    delay(1);
  }
}

// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066
