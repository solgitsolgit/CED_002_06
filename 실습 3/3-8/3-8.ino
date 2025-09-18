int mic_digital_in=2;
int sensorValue = 0;
void setup() {
    Serial.begin(9600);
}
void loop() {
    sensorValue = digitalRead(mic_digital_in);
    if(sensorValue == 0)
    {
        Serial.println("Sound detected!");
        delay(1000);
    }
}
// CED 002, group 06, 2020-14247 강신의
// CED 002, group 06, 2023-14669 임태현
// CED 002, group 06, 2025-17066 김정환