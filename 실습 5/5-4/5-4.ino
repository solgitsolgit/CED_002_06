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

    status = mfrc522.MIFARE_Read(block, buffer, &size);
    if (status != MFRC522::STATUS_OK) {
        Serial.print(F("MIFARE_read() failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        return;
    }
    else Serial.println(F("MIFARE_read() success: "));

    for(int i=0 ; i<18 ; i++){
        Serial.print(buffer[i]);
        Serial.print(",");
    }
}

void loop(){
}
// CED 002, group 06, 2020-14247 강신의
// CED 002, group 06, 2023-14669 임태현
// CED 002, group 06, 2025-17066 김정환