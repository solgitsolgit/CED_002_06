volatile int state = 0;
int sensorValue = 0;
int digital_inp = 0;
void detectSound()
{
    state = 1;
    delay(100);
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
        state = 0;
        Serial.println("sound!");
        sensorValue = analogRead(A0);
        Serial.println(sensorValue);
    }
    delay(100);
}
// CED 002, group 06, 2020-14247 강신의
// CED 002, group 06, 2023-14669 임태현
// CED 002, group 06, 2025-17066 김정환