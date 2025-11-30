#include <opencv2\opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

void main(void) {
    Mat src, dst;
    string winName1 = "Original";
    string winName2 = "Sharpened";
    int kernel_size = 3;

    src = imread("lena.jpg");
    if (src.empty()) return;
    dst = src.clone();

    if (kernel_size % 2 == 0) {
        kernel_size += 1;
    }

    namedWindow(winName1, WINDOW_AUTOSIZE);
    namedWindow(winName2, WINDOW_AUTOSIZE);
    imshow(winName1, src);

    for (kernel_size = 3; kernel_size <= 31; kernel_size += 2) {
        Mat gray;  cvtColor(src, gray, CV_BGR2GRAY);

        Mat gx, gy;
        Sobel(gray, gx, CV_16S, 1, 0, kernel_size);
        Sobel(gray, gy, CV_16S, 0, 1, kernel_size);

        Mat agx, agy;
        convertScaleAbs(gx, agx);
        convertScaleAbs(gy, agy);

        Mat edges;
        addWeighted(agx, 0.5, agy, 0.5, 0, edges);

        Mat edges_bgr;  cvtColor(edges, edges_bgr, CV_GRAY2BGR);

        addWeighted(src, 1.0, edges_bgr, 0.5, 0, dst);

        imshow(winName2, dst);
        cout << "kernel_size = " << kernel_size << endl;

        if (waitKey(100) >= 0)
            break;
    }

    waitKey(0);
}


// CED 002, group 06, 2020-14247 강신의
// CED 002, group 06, 2023-14669 임태현
// CED 002, group 06, 2025-17066 김정환