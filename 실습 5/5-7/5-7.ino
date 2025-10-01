#include <SPI.h>
#include <SD.h>
#include <ADXL345.h>
#include <Wire.h>

ADXL345 acc;
File myFile;
int CS=4; //sdcard

void setup() {
  SPI.begin();
  SPI.setDataMode(SPI_MODE3);
  Serial.begin(9600);

  pinMode(CS, OUTPUT);
  digitalWrite(CS, HIGH);

  SD.begin(4); // cs pin number를 입력변수로 입력
  acc.begin();
}

void loop() {
  double Xg, Yg, Zg;
  acc.read(&Xg, &Yg, &Zg); 
  myFile = SD.open("data.txt", FILE_WRITE);

  if (myFile) {
    Serial.print("Writing to data.txt...");
    
    // 가속도 값 기록
    myFile.print(Xg);
    myFile.print(",");
    myFile.print(Yg);
    myFile.print(",");
    myFile.println(Zg);

    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening data.txt");
  }

  delay(200);
}

// CED 002, group 06, 2020-14247 강신의
// CED 002, group 06, 2023-14669 임태현
// CED 002, group 06, 2025-17066 김정환