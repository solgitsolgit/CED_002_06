#include <ADXL345.h> // ADXL345 라이브러리 헤더 파일

ADXL345 acc;

void setup() {
  acc.begin();
  Serial.begin(9600);
  acc.setRange(acc.RANGE_16G); //센서 출력 범위를 16g로 늘림
  delay(100);
}

void loop() {
  double Xg, Yg, Zg; //가속도 저장 변수
  acc.read(&Xg, &Yg, &Zg);

  Serial.print(Xg); //가속도 값을 모니터에 출력
  Serial.print(",");
  Serial.print(Yg);
  Serial.print(",");
  Serial.println(Zg);
  delay(200);
}

// CED 002, group 06, 2020-14247 강신의
// CED 002, group 06, 2023-14669 임태현
// CED 002, group 06, 2025-17066 김정환