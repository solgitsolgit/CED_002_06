#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "lcd.h"

// CarHW.ino에서 선언된 전역 LCD 인스턴스를 재사용
//   LiquidCrystal_I2C lcd(0x27, 16, 2);
extern LiquidCrystal_I2C lcd;

void lcdInit() {
    // CarHW.InitHW()에서 이미 init()을 호출하고 있을 수도 있지만,
    // 모듈 독립성을 위해 여기서도 한 번 더 안전하게 초기화해준다.
    lcd.init();
    lcd.backlight();
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("System Ready");
    lcd.setCursor(0, 1);
    lcd.print("ANS: --");
}

void lcdPrintAnswer(int cellIndex) {
    lcd.clear();

    // 1줄: 안내 문구
    lcd.setCursor(0, 0);
    lcd.print("TTT Next Move");

    // 2줄: 정답 위치 출력
    lcd.setCursor(0, 1);
    lcd.print("ANS: ");

    if (cellIndex >= 1 && cellIndex <= 9) {
        lcd.print(cellIndex);
    } else {
        // 유효하지 않은 값이면 -- 로 표시
        lcd.print("--");
    }
}