#pragma once
#include "constants.h"

// ===== LFS Algorithm (임태현) =====

// LFS 주행 시작 전에 호출 (필요한 상태 변수 초기화)
void lfsInit();

// main loop에서 MODE_LFS일 때 반복적으로 호출
// 내부에서 lineRead(), motor*() 함수들을 사용해
// 왼쪽 우선 탐색(LFS) 주행을 수행
void lfsUpdate();
