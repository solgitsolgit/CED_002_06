#pragma once

// ===== LCD Controller (강신의 또는 공동) =====

// LCD 초기화
void lcdInit();

// 정답(다음에 둘 위치)을 "ANS: 9" 같은 형식으로 출력
void lcdPrintAnswer(int cellIndex);
