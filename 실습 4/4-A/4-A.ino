// 라이브러리 호출
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <TinyGPS.h>

/* This sample code demonstrates the normal use of a TinyGPS object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/

TinyGPS gps;
SoftwareSerial ss(4, 3);
LiquidCrystal_I2C lcd(0x27, 16, 2); // lcd 설정

void setup()
{
  Serial.begin(115200);
  ss.begin(9600);

  lcd.init();
  lcd.backlight(); // lcd 초기화 및 백라이트
  
  Serial.print("Simple TinyGPS library v. "); Serial.println(TinyGPS::library_version());
  Serial.println("by Mikal Hart");
  Serial.println();
}

void loop()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      char c = ss.read();
      // Serial.write(c); // uncomment this line if you want to see the GPS data flowing
      if (gps.encode(c)) // Did a new valid sentence come in?
        newData = true;
    }
  }


lcd.clear();
 
if (newData)
{
// lcd에 위치 데이터 출력
  float flat_lcd, flon_lcd;
  unsigned long age_lcd;
  gps.f_get_position(&flat_lcd, &flon_lcd, &age_lcd);
  
  lcd.setCursor(0, 0);
  lcd.print("LAT: ");
  lcd.print(flat_lcd == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat_lcd, 6);
  
  lcd.setCursor(0, 1);
  lcd.print("LON: ");
  lcd.print(flon_lcd == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon_lcd, 6);
}
else
{
// ERROR 발생시 1초 간격으로 SCUM ERR, CHARS, SENTENCES값 lcd에 출력
  unsigned long chars_lcd;
  unsigned short sentences_lcd, failed_lcd;
  gps.stats(&chars_lcd, &sentences_lcd, &failed_lcd);

  static int displayMode = 0;
  
  lcd.setCursor(0, 0); 
  switch (displayMode) {
    case 0:
      lcd.print("CHARS: ");
      lcd.print(chars_lcd);
      break;
    case 1:
      lcd.print("SENTENCES: ");
      lcd.print(sentences_lcd);
      break;
    case 2:
      lcd.print("CSUM ERR: ");
      lcd.print(failed_lcd);
      break;
  }
  displayMode = (displayMode + 1) % 3;
}

  if (newData)
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("LAT=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" LON=");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.print(" SAT=");
    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial.print(" PREC=");
    Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
  }
  
  gps.stats(&chars, &sentences, &failed);
  Serial.print(" CHARS=");
  Serial.print(chars);
  Serial.print(" SENTENCES=");
  Serial.print(sentences);
  Serial.print(" CSUM ERR=");
  Serial.println(failed);
  if (chars == 0)
    Serial.println("** No characters received from GPS: check wiring **");
}

// CED 002, group 06, 2020-14247, 강신의
// CED 002, group 06, 2023-14669, 임태현
// CED 002, group 06, 2025-17066, 김정환