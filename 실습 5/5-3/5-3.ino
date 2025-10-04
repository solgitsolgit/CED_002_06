#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println(F("Ready. Scan a MIFARE Classic card..."));

  // 키 초기화 (공장 기본키)
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
}

void loop() {
  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));

  // 카드가 있는지 확인
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  if (!mfrc522.PICC_ReadCardSerial()) return;

  // UID 출력
  Serial.print(F("Card UID: "));
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  // 태그 타입 확인 (MIFARE Classic 계열만 처리)
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  Serial.print(F("PICC type: "));
  Serial.println(mfrc522.PICC_GetTypeName(piccType));
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("This sketch only works with MIFARE Classic cards."));
    mfrc522.PICC_HaltA();
    return;
  }

  // --- 설정: 섹터/블록 ---
  byte sector = 0;           // 섹터 0
  byte blockAddr = 1;        // 섹터0의 블록1 (쓰고자 하는 블록)
  byte trailerBlock = sector * 4 + 3; // 섹터의 트레일러 블록(인증 대상)

  // 쓸 데이터 (정확히 16바이트)
  byte writeData[16] = {
    0x01,0x02,0x03,0x04, 0x05,0x06,0x07,0x08,
    0x09,0x0A,0x09,0x08, 0x07,0x06,0x05,0x04
  };

  // --- 인증 (Key A) ---
  MFRC522::StatusCode status;
  Serial.println(F("Authenticating with Key A..."));
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    mfrc522.PICC_HaltA();
    return;
  }

  // 현재 섹터 덤프(디버그 용)
  Serial.println(F("Current data in sector:"));
  mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, sector);
  Serial.println();

  // --- 블록 쓰기 ---
  Serial.print(F("Writing to block "));
  Serial.print(blockAddr);
  Serial.println(F(" ..."));
  status = mfrc522.MIFARE_Write(blockAddr, writeData, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Write() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    mfrc522.PCD_StopCrypto1();
    mfrc522.PICC_HaltA();
    return;
  }
  Serial.println(F("Write complete."));

  // --- 블록 읽기(검증) ---
  byte readBuf[18];
  byte size = sizeof(readBuf);
  Serial.print(F("Reading back block "));
  Serial.print(blockAddr);
  Serial.println(F(" ..."));
  status = mfrc522.MIFARE_Read(blockAddr, readBuf, &size);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Read() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
  } else {
    Serial.print(F("Data read:"));
    for (byte i = 0; i < 16; i++) {
      Serial.print(readBuf[i] < 0x10 ? " 0" : " ");
      Serial.print(readBuf[i], HEX);
    }
    Serial.println();
  }

  // 섹터 덤프(변경 후)
  Serial.println(F("Current data in sector (after write):"));
  mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, sector);
  Serial.println();

  // 정리: halt & stop crypto
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
  
  Serial.println(F("Please remove card..."));
  // 카드가 제거될 때까지 기다림
  while (mfrc522.PICC_IsNewCardPresent()) {
    delay(1);
  }
  Serial.println(F("Card removed. Ready for next."));


  // 잠깐 대기 (중복 쓰기 방지)
  delay(1);
}
// CED 002, group 06, 2020-14247 강신의
// CED 002, group 06, 2023-14669 임태현
// CED 002, group 06, 2025-17066 김정환