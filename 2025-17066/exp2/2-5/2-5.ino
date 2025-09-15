int buzzer_out6 = 6;
int buzzer_out3 = 3;

void setup() {
  pinMode(buzzer_out6, OUTPUT);
  pinMode(buzzer_out3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  tone(buzzer_out6, 300);
  Serial.print("duty cycle = 50%, frequency = 300");
  delay(1000);
  tone(buzzer_out6, 600);
  Serial.print("duty cycle = 50%, frequency = 600");
  delay(1000);
  tone(buzzer_out6, 900);
  Serial.print("duty cycle = 50%, frequency = 900");
  delay(1000);
  tone(buzzer_out6, 1200);
  Serial.print("duty cycle = 50%, frequency = 1200");
  delay(1000);

  analogWrite(buzzer_out6, 0);
  Serial.print("duty cycle = 0%, frequency = 980");
  delay(1000);
  analogWrite(buzzer_out6, 64);
  Serial.print("duty cycle = 25%, frequency = 980");
  delay(1000);
  analogWrite(buzzer_out6, 127);
  Serial.print("duty cycle = 50%, frequency = 980");
  delay(1000);
  analogWrite(buzzer_out6, 255);
  Serial.print("duty cycle = 100%, frequency = 980");
  delay(1000);

  tone(buzzer_out3, 490);
  Serial.print("duty cycle = 50%, frequency = 490");
  delay(1000);
  analogWrite(buzzer_out3, 127);
  Serial.print("duty cycle = 50%, frequency = 490");
  delay(1000);
}

// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066

