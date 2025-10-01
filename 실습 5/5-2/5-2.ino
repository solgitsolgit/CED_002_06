// 라이브러리 호출 및 핀설정
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

// 통신 및 모듈 초기화 
void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Scan Card to see UID and type...");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return; // 새로운 카드 확인
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return; // 카드(PICC) 선택 후 read
  }
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));  // debug info 시리얼 모니터에 출력
}

// CED 002, group 06, 2020-14247, 강신의
// CED 002, group 06, 2023-14669, 임태현
// CED 002, group 06, 2025-17066, 김정환
