int mic_analog_in = A0;
int sensorValue = 0;

void setup() {
    Serial.begin(9600);
}

void loop() {
    sensorValue = analogRead(mic_analog_in);
    Serial.println(sensorValue, DEC);
    delay(100);
}
// CED 002, group 06, 2020-14247 , 강신의
// CED 002, group 06, 2023-14669 , 임태현
// CED 002, group 06, 2025-17066 , 김정환