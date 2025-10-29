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
