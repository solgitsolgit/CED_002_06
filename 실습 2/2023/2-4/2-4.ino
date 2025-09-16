#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);
  lcd.print("Hello");
  lcd.setCursor(7,0);
  lcd.print("world");
  delay(3000);
  lcd.clear();
  lcd.print("I am Arduino");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("ShinYee Kang");
  lcd.setCursor(0,1);
  lcd.print("JungHwan Kim");
  delay(3000);
  lcd.clear();
}

// group 6 2023-14669