#include <opencv2\opencv.hpp>
#include <iostream>
#include "lab10.h"

using namespace std;
using namespace cv;

int main3() {
	Mat src, dst;
	string winName1 = "Original";
	string winName2 = "Blurred";
	int kernel_size = 3;

	src = imread("lena.jpg");
	dst = src.clone();


	if (kernel_size % 2 == 0) {
		kernel_size += 1;
	}

	/*
	insert your code
	*/

	namedWindow(winName1, WINDOW_AUTOSIZE);
	namedWindow(winName2, WINDOW_AUTOSIZE);
	imshow(winName1, src);

	for (kernel_size = 3; kernel_size <= 31; kernel_size += 2) {
		GaussianBlur(src, dst, Size(kernel_size, kernel_size), 0);
		imshow(winName2, dst);
		cout << "kernel_size = " << kernel_size << endl;
		if (waitKey(100) >= 0)
			break;
	}
	
	waitKey(0);
	return 0;
}
