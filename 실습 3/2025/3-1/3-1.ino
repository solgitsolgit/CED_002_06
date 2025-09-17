int mic_analog_in = A0;
int sensorValue = 0;

void setup() {
    Serial.begin(9600);
}

void loop() {
    sensorValue = analogRead(mic_analog_in);
    Serial.println(sensorValue, DEC);
}

// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066