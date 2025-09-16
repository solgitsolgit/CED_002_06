#include <IRremote.h>
#include <LiquidCrystal_I2C.h>

const int receiverPin = 8;
IRrecv irrecv(receiverPin);
decode_results results;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  lcd.init();
  lcd.backlight();
}

void loop() {
  if (irrecv.decode(&results)) {
    lcd.clear();
    lcd.setCursor(0, 0);

    if (results.value == 0xFF6897) {
      lcd.print("0");
    }
    else if (results.value == 0xFF30CF) {
      lcd.print("1");
    }
    else if (results.value == 0xFF18E7) {
      lcd.print("2");
    }
    else if (results.value == 0xFF7A85) {
      lcd.print("3");
    }
    else if (results.value == 0xFF10EF) {
      lcd.print("4");
    }
    else if (results.value == 0xFF38C7) {
      lcd.print("5");
    }
    else if (results.value == 0xFF5AA5) {
      lcd.print("6");
    }
    else if (results.value == 0xFF42BD) {
      lcd.print("7");
    }
    else if (results.value == 0xFF4AB5) {
      lcd.print("8");
    }
    else if (results.value == 0xFF52AD) {
      lcd.print("9");
    }
    delay(500);
    irrecv.resume();
  }
}

// CED 002, group 06, 2020-14247
// CED 002, group 06, 2023-14669
// CED 002, group 06, 2025-17066
