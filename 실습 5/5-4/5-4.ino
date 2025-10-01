#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;

void setup(){
    Serial.begin(9600);
    SPI.begin();
    mfrc522.PCD_Init();
    Serial.println("Scan Card to see UID and type...");

    // 기본 키 초기화 (공장 기본키)
    for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

    // --- 카드가 리더에 올 때까지 대기 ---
    while (!mfrc522.PICC_IsNewCardPresent()) {
      delay(50);
    }
    if (!mfrc522.PICC_ReadCardSerial()) {
      Serial.println(F("Failed to read card serial."));
      return;
    }

    // (선택) UID 출력
    Serial.print(F("Card UID:"));
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
      Serial.print(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println();

    // 읽고자 하는 블록 설정
    byte block = 1; // 섹터0의 블록1
    byte trailerBlock = (block / 4) * 4 + 3; // 해당 섹터의 트레일러 블록

    // 인증 (Key A)
    MFRC522::StatusCode status;
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
      Serial.print(F("PCD_Authenticate() failed: "));
      Serial.println(mfrc522.GetStatusCodeName(status));
      mfrc522.PICC_HaltA();
      return;
    }

    // 읽기 버퍼 준비 (라이브러리 권장 크기: 18)
    byte buffer[18];
    byte size = sizeof(buffer);

    status = mfrc522.MIFARE_Read(block, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_Read() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        mfrc522.PCD_StopCrypto1();
        mfrc522.PICC_HaltA();
        return;
    } else {
        Serial.println(F("MIFARE_Read() success:"));
    }

    // 실제 읽은 데이터(일반적으로 16바이트)를 출력
    // size는 호출 후 실제 바이트 수로 업데이트 될 수 있음. 안전하게 min(size,16)만 출력.
    byte toPrint = (size < 16) ? size : 16;
    for (byte i = 0; i < toPrint; i++) {
        Serial.print(buffer[i]);
        Serial.print(",");
    }
    Serial.println();

    // 정리
    mfrc522.PCD_StopCrypto1();
    mfrc522.PICC_HaltA();
}

void loop(){
  // setup에서만 읽기 1회 수행
}
// CED 002, group 06, 2020-14247 강신의
// CED 002, group 06, 2023-14669 임태현
// CED 002, group 06, 2025-17066 김정환