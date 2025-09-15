#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();

}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Hello");
  lcd.setCursor(7, 0);
  lcd.print("world");
  delay(3000);
  lcd.clear();

  lcd.print("I am Arduino");
  delay(3000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("ShinYee Kang");
  lcd.setCursor(0, 1);
  lcd.print("Lim, Kim");
  delay(3000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("TaeHyun Lim");
  lcd.setCursor(0, 1);
  lcd.print("Kang, Kim");
  delay(3000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("JungHwan Kim");
  lcd.setCursor(0, 1);
  lcd.print("Kang, Lim");
  delay(3000);
  lcd.clear();
}

// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066
