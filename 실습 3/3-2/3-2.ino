int mic_inp = 2;
int sensorValue = 0;
void setup() {
    Serial.begin(9600);
    pinMode(mic_inp, INPUT);
}

void loop() {
    sensorValue = digitalRead(mic_inp);
    Serial.println(sensorValue, DEC);// 입력된 값을 10진법으로 표시
    delay(30);
}
// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066