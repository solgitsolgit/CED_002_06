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

    for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
    byte buffer[16]={1,2,3,4,5,6,7,8,9,10,9,8,7,6,5,4}; //ID card에 저장할 데이터 입력
    byte block, status;
    block = 1; //저장할 블록번호 설정, 1번 블록에 저장
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A,block,&key,&(mfrc522.uid));
    status = mfrc522.MIFARE_Write(block, buffer, 16);

    Serial.println(F("Current data in sector:"));
    mfrc522.PICC_DumpMifareClassicSectorToSerial(&(mfrc522.uid), &key, block/4);
    Serial.println();
}

void loop(){
}
// CED 002, group 06, 2020-14247 강신의
// CED 002, group 06, 2023-14669 임태현
// CED 002, group 06, 2025-17066 김정환