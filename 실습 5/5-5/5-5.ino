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
    Serial.println("Scan Card to see UID and type...");

    for (byte i = 0; i < 6; i++) newKey.keyByte[i] = 0x11;
    for (byte i = 0; i < 6; i++) oldKey.keyByte[i] = 0xFF;
    byte buffer[16]={0x11,0x11,0x11,0x11,0x11,0x11,0xff,0x07,0x80,0x69,0xff,0xff,0xff,0xff,0xff,0xff}; //ID card에 저장할 데이터 입력
    byte block, status;
    block = 3; // 섹터 0의 trailer 블록 번호 설정

    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,block,&newKey,&(mfrc522.uid));
    status = mfrc522.MIFARE_Write(block, buffer, 16);

    Serial.println(F("Current data in sector:"));
    mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &newKey, block/4);
    Serial.println();
}

void loop(){
}
// CED 002, group 06, 2020-14247 강신의
// CED 002, group 06, 2023-14669 임태현
// CED 002, group 06, 2025-17066 김정환