#include <opencv2/opencv.hpp>
#include <iostream>
#include "lab10.h"

using namespace cv;
using namespace std;

int main1() {
	Mat src;
	string windowName = "LENA";
	src = imread("lena.jpg");
	imshow(windowName, src);
	waitKey(0);
	return 0;
}
// CED 002, group 06, 2020-14247 강신의
// CED 002, group 06, 2023-14669 임태현
// CED 002, group 06, 2025-17066 김정환