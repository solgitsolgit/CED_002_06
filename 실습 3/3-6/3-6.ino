int light = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int reading = analogRead(light);
  Serial.println(reading);
  delay(500);
}

// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066