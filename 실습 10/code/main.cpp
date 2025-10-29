#include <opencv2/opencv.hpp>
#include <iostream>
#include "lab10.h"

using namespace cv;
using namespace std;

#include <fstream>
#include <windows.h>
#include <conio.h>  // _getch()

static bool file_exists(const char* p) { std::ifstream f(p); return f.good(); }

void print_cwd_and_files() {
    char buf[MAX_PATH]{ 0 };
    GetCurrentDirectoryA(MAX_PATH, buf);
    std::cout << "[CWD] " << buf << std::endl;

    std::cout << "[exists] lena.jpg:   " << (file_exists("lena.jpg") ? "yes" : "no") << std::endl;
    std::cout << "[exists] sample.mp4: " << (file_exists("sample.mp4") ? "yes" : "no") << std::endl;
}

int main() {
    while (true) {
        system("cls");
        print_cwd_and_files();
        cout << "\n===== Lab10 실험 선택 =====\n";
        cout << "  1) 실험 1 (main1)\n";
        cout << "  2) 실험 2 (main2)\n";
        cout << "  3) 실험 3 (main3)\n";
        cout << "  4) 실험 4 (main4)\n";
        cout << "  q) 종료\n";
        cout << "번호를 입력하세요: ";

        string line;
        if (!std::getline(cin, line)) break;
        if (line.empty()) continue;

        if (line == "q" || line == "Q") {
            cout << "종료합니다.\n";
            break;
        }

        int sel = 0;
        try { sel = std::stoi(line); }
        catch (...) { sel = 0; }

        switch (sel) {
        case 1:
            cout << "\n[실행] main1()\n";
            main1();
            break;
        case 2:
            cout << "\n[실행] main2()\n";
            main2();
            break;
        case 3:
            cout << "\n[실행] main3()\n";
            main3();
            break;
        case 4:
            cout << "\n[실행] main4()\n";
            main4();
            break;
        default:
            cout << "유효하지 않은 입력입니다.\n";
            break;
        }

        // 실험 종료 후 모든 OpenCV 윈도우 닫기
        destroyAllWindows();

        cout << "\n아무 키나 누르면 메뉴로 돌아갑니다...";
        _getch();  // 키 한 번 입력 대기
    }

    return 0;
}
// CED 002, group 06, 2020-14247 강신의
// CED 002, group 06, 2023-14669 임태현
// CED 002, group 06, 2025-17066 김정환