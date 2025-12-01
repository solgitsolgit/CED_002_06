#include "ttt_scan.h"

namespace {
    // 스캔 관련 파라미터들 (실험으로 튜닝 필수)
    const int   SCAN_SPEED          = 150;     // SetSpeed()에 들어갈 속도
    const float CUP_THRESHOLD_CM    = 20.0f;   // 이 거리보다 가까우면 컵 있다고 판단
    const unsigned long SAMPLE_INTERVAL_MS = 30;  // 초음파 샘플링 주기(ms)

    // rowIndex: 0 = 윗줄(1,2,3), 1 = 중간줄(4,5,6), 2 = 아래줄(7,8,9)
    void followSegmentAndScanRow(BoardState &board, int rowIndex) {
        float minLeft  = 9999.0f;
        float minRight = 9999.0f;

        SetSpeed(SCAN_SPEED);
        MoveFront();

        unsigned long lastSample = millis();

        while (true) {
            uint8_t lv = lineRead();

            // ===== 라인 유지 제어 (아주 단순 버전, 이후 튜닝 필요) =====
            // 비트마스크:
            // 왼쪽: 0x04, 중앙: 0x02, 오른쪽: 0x01
            bool leftOn   = (lv & 0x04) != 0;
            bool centerOn = (lv & 0x02) != 0;
            bool rightOn  = (lv & 0x01) != 0;

            // 교차점(3개 센서 모두 검정) 도달 시: 이번 row 스캔 끝
            if (lineIsIntersection(lv)) {
                StopCar();
                break;
            }

            // 라인 추종: 굉장히 러프한 P-제어 느낌
            if (centerOn && !leftOn && !rightOn) {
                // 중앙만 검정 → 직진
                MoveFront();
            } else if (leftOn && !centerOn) {
                // 왼쪽 쪽만 검정 → 라인이 왼쪽에 있음 → 약간 좌측으로 정렬해야 하는데
                // 차가 이미 라인 오른쪽에 있는 구조라면 TurnLeft/TurnRight는
                // 실제 트랙/차 구조에 따라 바꿔야 함.
                TurnLeft();
            } else if (rightOn && !centerOn) {
                TurnRight();
            } else {
                // 애매한 상태(센서 다 끊기거나 이상한 조합) → 속도 줄인 직진 등
                MoveFront();
            }

            // ===== 초음파 샘플링 =====
            unsigned long now = millis();
            if (now - lastSample >= SAMPLE_INTERVAL_MS) {
                lastSample = now;

                float dL = usReadLeftCm();
                float dR = usReadRightCm();

                if (dL > 0 && dL < minLeft)   minLeft  = dL;
                if (dR > 0 && dR < minRight)  minRight = dR;
            }
        }

        // ===== rowIndex에 따른 보드 인덱스 매핑 =====
        // row 0: cells 0,1,2 (1,2,3)
        // row 1: cells 3,4,5 (4,5,6)
        // row 2: cells 6,7,8 (7,8,9)
        int leftIdx  = rowIndex * 3 + 0;  // 왼쪽 열
        int rightIdx = rowIndex * 3 + 2;  // 오른쪽 열

        if (minLeft < CUP_THRESHOLD_CM) {
            board.cell[leftIdx] = CELL_OTHER;
        }
        if (minRight < CUP_THRESHOLD_CM) {
            board.cell[rightIdx] = CELL_OTHER;
        }
        // 가운데 열(2,5,8)은 후속 패스에서 채울 예정
    }

    // 중앙 열(2,5,8) 스캔
    //  - 중앙 교차점에서 좌/우로 이동하며 필요한 구간에서만 초음파 측정
    //  - 실제 트랙을 보고 설계해야 해서, 지금은 스켈레톤만
    void scanCenterColumn(BoardState &board) {
        // TODO:
        // 1) 현재 위치를 중앙 교차점으로 맞춘 상태라고 가정
        // 2) motorTurnLeft90() 또는 motorTurnRight90()으로 가로 중앙 라인으로 진입
        // 3) MoveFront()하면서 일정 구간마다 usReadLeftCm()/usReadRightCm()를 측정
        // 4) board.cell[1], cell[4], cell[7] (2,5,8번 칸)에 대한 min distance 기반 판정
        //
        // 예시 뼈대:
        /*
        SetSpeed(SCAN_SPEED);
        MoveFront();
        float minCenter1 = 9999.0f;
        float minCenter2 = 9999.0f;
        float minCenter3 = 9999.0f;

        // 중앙 열의 각 칸에 해당하는 세그먼트를 어떻게 나눌지
        // 실제 라인과 교차점 위치를 보고 결정해야 함.
        */
    }
} // namespace

// ----------------- 공개 함수 구현 -----------------

void tttScanInit(BoardState &board) {
    for (int i = 0; i < 9; ++i) {
        board.cell[i] = CELL_EMPTY;
    }
}

void tttScanBoard(BoardState &board) {
    // 0. 시작 상태 가정:
    //    - 세로 중앙 라인의 맨 위 교차점(또는 그 직전)에 있고,
    //    - 아래 방향을 보고 있음

    // 1. 윗줄(1,3) 스캔
    followSegmentAndScanRow(board, 0);

    // 2. 중간줄(4,6) 스캔
    followSegmentAndScanRow(board, 1);

    // 3. 아랫줄(7,9) 스캔
    followSegmentAndScanRow(board, 2);

    // 4. 중앙 열(2,5,8) 추가 스캔 (트랙 확인 후 구현)
    // scanCenterColumn(board);

    // 5. 정지 (필요시 시작 위치 복귀 루틴 추가)
    StopCar();
}
