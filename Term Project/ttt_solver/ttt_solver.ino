#include <Arduino.h>

/*
  ====== 네가 매번 수정하는 부분 ======
  전체 놓인 말 위치들(내 말 + 상대 말)을 1~9 숫자만으로 적어줘.
  - 예: "1357" 또는 "1 3 5 7" (구분자는 있어도/없어도 됨)
  - 0 같은 종료 표식은 사용하지 않음
*/
const char OCCUPIED_STR[] = "1 3 5 7";  // TODO: 여기만 매번 바꾸기

// 승리 패턴 (1~9 -> bit0~bit8)
static const uint16_t WIN_MASKS[8] = {
  0b000000111, // 1,2,3
  0b000111000, // 4,5,6
  0b111000000, // 7,8,9
  0b001001001, // 1,4,7
  0b010010010, // 2,5,8
  0b100100100, // 3,6,9
  0b100010001, // 1,5,9
  0b001010100  // 3,5,7
};

static inline uint16_t bitOfPos(int pos1to9) {
  return (pos1to9 >= 1 && pos1to9 <= 9) ? (uint16_t)(1u << (pos1to9 - 1)) : 0;
}

static bool isWin(uint16_t mask) {
  for (int i = 0; i < 8; i++) {
    if ((mask & WIN_MASKS[i]) == WIN_MASKS[i]) return true;
  }
  return false;
}

// "1357" 또는 "1 3 5 7" 같은 문자열에서 1~9만 뽑아 마스크로 만듦
static uint16_t maskFromDigits(const char* s) {
  uint16_t m = 0;
  for (int i = 0; s[i] != '\0'; i++) {
    char c = s[i];
    if (c >= '1' && c <= '9') m |= bitOfPos(c - '0');
  }
  return m;
}

// 시리얼 한 줄(엔터까지)에서 '1'~'9'만 읽어 내 돌 마스크 생성 (중복 자동 제거)
static uint16_t readMyMaskFromSerialLine() {
  uint16_t m = 0;
  while (true) {
    while (!Serial.available()) {}
    char c = (char)Serial.read();
    if (c == '\r') continue;
    if (c == '\n') break;
    if (c >= '1' && c <= '9') m |= bitOfPos(c - '0');
  }
  return m;
}

// (1) 즉시 승리, (2) 즉시 차단만. 없으면 -1
static int findMove(uint16_t myMask, uint16_t oppMask) {
  uint16_t occ = myMask | oppMask;

  // 1) 내가 두면 바로 이김
  for (int pos = 1; pos <= 9; pos++) {
    uint16_t b = bitOfPos(pos);
    if ((occ & b) == 0 && isWin(myMask | b)) return pos;
  }

  // 2) 상대가 다음 수에 이기는 걸 막음
  for (int pos = 1; pos <= 9; pos++) {
    uint16_t b = bitOfPos(pos);
    if ((occ & b) == 0 && isWin(oppMask | b)) return pos;
  }

  return -1;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  // 1) 코드에 박힌 "전체 점유(내+상대)" 마스크
  const uint16_t occMask = maskFromDigits(OCCUPIED_STR);

  // 2) 입력으로 "내 돌 위치"만 받음 (예: 3 7)
  uint16_t myInputMask = readMyMaskFromSerialLine();

  // 안전 처리: 내 입력은 전체 점유칸 안에 있는 것만 인정
  uint16_t myMask = myInputMask & occMask;
  uint16_t oppMask = occMask & (~myMask);

  // 3) 정답 계산 후 숫자 하나만 출력
  int ans = findMove(myMask, oppMask);
  Serial.println(ans);
}
