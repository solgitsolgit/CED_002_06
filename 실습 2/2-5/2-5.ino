int buzzer_out = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzer_out, OUTPUT);
  Serial.begin(9600);
}

// void loop() {
//   // put your main code here, to run repeatedly:
//   tone(buzzer_out, 300);
//   Serial.println("duty cycle = 50%, frequency = 300");
//   delay(1000);
//   tone(buzzer_out, 600);
//   Serial.println("duty cycle = 50%, frequency = 600");
//   delay(1000);
//   tone(buzzer_out, 900);
//   Serial.println("duty cycle = 50%, frequency = 900");
//   delay(1000);
//   tone(buzzer_out, 1200);
//   Serial.println("duty cycle = 50%, frequency = 1200");
//   delay(1000);

//   analogWrite(buzzer_out, 0);
//   Serial.println("duty cycle = 0%, frequency = 980");
//   delay(1000);
//   analogWrite(buzzer_out, 64);
//   Serial.println("duty cycle = 25%, frequency = 980");
//   delay(1000);
//   analogWrite(buzzer_out, 127);
//   Serial.println("duty cycle =50%, frequency = 980");
//   delay(1000);
//   analogWrite(buzzer_out, 255);
//   Serial.println("duty cycle = 100%, frequency = 980");
//   delay(1000);
// }

void loop() {
  // put your main code here, to run repeatedly:
  tone(buzzer_out, 490);
  Serial.println("duty cycle = 50%, frequency = 490");
  delay(1000);

  analogWrite(buzzer_out, 127);
  Serial.println("duty cycle =50%, frequency = 490");
  delay(1000);
}

//group 6 2023-14669
