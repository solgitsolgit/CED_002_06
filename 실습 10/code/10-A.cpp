#include <opencv2\opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void main(void) {
    Mat src, down_nearest, blurred, down_blur;

    src = imread("alias_test.jpg");
    if (src.empty()) return;

    //커널 크기를 5로 잡은 가우시안 블러
    GaussianBlur(src, blurred, Size(5, 5), 0);

    // 0.25배 축소 
    resize(src, down_nearest, Size(), 0.25, 0.25, 0);
    resize(blurred, down_blur, Size(), 0.25, 0.25, 0);

    imshow("Only Downsample", down_nearest);
    imshow("Gaussian And Downsample", down_blur);
    waitKey(0);
}

// CED 002, group 06, 2020-14247 강신의
// CED 002, group 06, 2023-14669 임태현
// CED 002, group 06, 2025-17066 김정환