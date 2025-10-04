#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;
byte size;
byte buffer[16] = {
  0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 
  0xff, 0x07, 0x80, 0x69, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};
byte block, status;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xff; 
  
  block = 7; 
  size = sizeof(buffer);
  
  Serial.println("Scan Card to change Key A to 0x11...");
}

void loop() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print("PCD_Authenticate() failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    mfrc522.PICC_HaltA(); 
    return;
  }
  Serial.println("Authentication success with 0xFF key. Writing new Key A...");

  status = mfrc522.MIFARE_Write(block, buffer, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("MIFARE_Write() failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
  } else {
    Serial.println("Key A successfully changed to 0x11...");
  }
  
  mfrc522.PCD_StopCrypto1();
  mfrc522.PICC_HaltA(); 
  delay(1000); 
}

// CED 002, group 06, 2020-14247, 강신의
// CED 002, group 06, 2023-14669, 임태현
// CED 002, group 06, 2025-17066, 김정환
