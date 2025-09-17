int light = A0;
int ledpin = 3;

void setup() {
  pinMode(ledpin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int reading = analogRead(light);
  //값을 받아들여 500 이상으로 어두워지면 불을 키고 아니면 끄기
    if(reading>500){
      digitalWrite(ledpin, HIGH);
    } else{
      digitalWrite(ledpin, LOW);
    }
}

// CED 002, group 06, 2020-14247 강신의
// CED 002, group 06, 2023-14669 임태현
// CED 002, group 06, 2025-17066 김정환