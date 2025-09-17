int mic_analog_in = 0;
int sensorValue = 0;
void setup() {
    Serial.begin(9600);
}

void loop() {
    sensorValue = digitalRead(mic_analog_in);
    Serial.println(sensorValue, DEC);// 입력된 값을 10진법으로 표시한대
}
// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066