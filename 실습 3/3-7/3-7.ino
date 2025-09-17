volatile int state = 0;
int sensorValue = 0;
int digital_inp = 0;
void detectSound()
{
    state = 1;
}

void setup() {
    Serial.begin(9600);
    attachInterrupt(digital_inp, detectSound,LOW);
}

void loop() {
    digital_inp = digitalRead(2);
    //Serial.println(digital_inp);
    if(state == 1)// 인터럽트가 발생하였을 시에 메세지 출력
    {
        Serial.println("sound!");
        sensorValue = analogRead(A0);
        Serial.println(sensorValue);
        state = 0;
    }
    delay(10);
}
// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066