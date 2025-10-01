#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key oldKey;
MFRC522::MIFARE_Key newKey;

void setup(){
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println(F("Scan Card to change Key A on sector 0 trailer (block 3) ..."));

  // 키 초기화
  for (byte i = 0; i < 6; i++) oldKey.keyByte[i] = 0xFF; // 기존키 (공장 기본)
  for (byte i = 0; i < 6; i++) newKey.keyByte[i] = 0x11; // 새 키(0x11..)

  // 카드가 리더에 올 때까지 대기
  while (!mfrc522.PICC_IsNewCardPresent()) {
    delay(50);
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    Serial.println(F("Failed to read card serial."));
    return;
  }

  // UID 출력(디버그)
  Serial.print(F("Card UID:"));
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();

  // 대상 섹터/블록 설정 (섹터0의 트레일러 블록 = 3)
  byte sector = 0;
  byte trailerBlock = sector * 4 + 3; // =3

  // 새로 쓸 트레일러 데이터: KeyA(6)=0x11..., AccessBytes(4)= {0xFF,0x07,0x80,0x69}, KeyB(6)=0xFF...
  byte trailerNew[16] = {
    0x11,0x11,0x11,0x11,0x11,0x11, // Key A -> new (0x11...)
    0xFF,0x07,0x80,0x69,           // Access bits (일반적인 값)
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF  // Key B (원래 그대로 유지)
  };

  // 원래로 복원할 트레일러(원래 KeyA = 0xFF...)
  byte trailerOrig[16] = {
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, // Key A -> original
    0xFF,0x07,0x80,0x69,           // Access bits (같이 유지)
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF  // Key B
  };

  MFRC522::StatusCode status;

  // 1) 기존 키로 트레일러 인증 (중요!)
  Serial.println(F("Authenticating with OLD key (to allow writing trailer)..."));
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &oldKey, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("PCD_Authenticate() with OLD key failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    mfrc522.PICC_HaltA();
    return;
  }

  // 2) 트레일러(키A)를 새 키로 덮어쓰기
  Serial.println(F("Writing new trailer (KeyA=0x11...) ..."));
  status = mfrc522.MIFARE_Write(trailerBlock, trailerNew, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Write() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    // 안전하게 끝내기
    mfrc522.PCD_StopCrypto1();
    mfrc522.PICC_HaltA();
    return;
  }
  Serial.println(F("Trailer written (new KeyA)."));

  // 종료(암호화 해제) — 다음 동작에서 새 키로 접근할 수 있게 함
  mfrc522.PCD_StopCrypto1();
  mfrc522.PICC_HaltA();

  // 3) 새 키로 섹터 덤프(검증)
  Serial.println(F("Dumping sector with NEW key (to verify change)..."));
  // PICC_Dump 내부에서 인증 시도하므로 새 키 전달
  mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &newKey, sector);
  Serial.println();

  // 4) 이번에는 새 키로 인증한 뒤 원래 트레일러로 복원
  Serial.println(F("Authenticating with NEW key (to restore original KeyA)..."));
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &newKey, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("PCD_Authenticate() with NEW key failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    // 여기서 복원이 불가하면 카드에 잠길 수 있으니 매우 조심
    mfrc522.PICC_HaltA();
    return;
  }

  Serial.println(F("Restoring original trailer (KeyA=0xFF...) ..."));
  status = mfrc522.MIFARE_Write(trailerBlock, trailerOrig, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Write() restore failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    mfrc522.PCD_StopCrypto1();
    mfrc522.PICC_HaltA();
    return;
  }
  Serial.println(F("Trailer restored to original."));

  mfrc522.PCD_StopCrypto1();
  mfrc522.PICC_HaltA();

  // 5) 최종 확인 (원래 키로 덤프)
  Serial.println(F("Final dump with ORIGINAL key (sanity check):"));
  mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &oldKey, sector);
  Serial.println();

  Serial.println(F("Done. Remove card."));
}

void loop(){
  // 빈 루프. setup()에서 한 번만 실행됩니다.
}
// CED 002, group 06, 2020-14247 강신의
// CED 002, group 06, 2023-14669 임태현
// CED 002, group 06, 2025-17066 김정환