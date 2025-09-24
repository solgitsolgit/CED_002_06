#define TRIGGER_PIN 12
#define ECHO_PIN 11

void setup()
{
    Serial.begin(9600);
    pinMode(TRIGGER_PIN, OUTPUT); // 센서 Trig 핀 = D12 pinMode(ECHO_PIN, INPUT); // 센서 Echo 핀 = D11
}

void loop()
{
    long duration, cm;
    digitalWrite(TRIGGER_PIN, HIGH); // 센서에 Trig 신호 입력
    delayMicroseconds(10); // 10us 저도 유지
    digitalWrite(TRIGGER_PIN, LOW); // Trig 신호 off
    duration = pulseIn(ECHO_PIN, HIGH); // Echo pin: HIGH -> LOW 간격을 측정
    cm = microsecondsToCentimeters(duration); //거리(cm) 단위 변환
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    delay(300); // 0.3초 대기후 다시 측정
}

long microsecondsToInches(long microseconds)
{
    return microseconds/74/2; //소리의 공기 중 속력은 약 73.746us/inch이다.
}

long microsecondsToCentimeters(long microseconds)
{
    return microseconds/29/2; //소리의 공기 중 속력은 약 29us/cm이다. (340m/s)
}

// CED 002, group 06, 2020-14247 강신의
// CED 002, group 06, 2023-14669 임태현
// CED 002, group 06, 2025-17066 김정환