#include <opencv2\opencv.hpp>
#include <iostream>
#include "lab10.h"

using namespace std;
using namespace cv;

void main4(void) {
	char keychar;
	Mat frame;
	Mat src, dst;
	string winName1 = "Original";
	string winName2 = "Edge";
	int scale = 1;
	int delta = 0;
	int kernel_size = 3;
	int ddepth = CV_16S;

	VideoCapture vid_in = VideoCapture("sample.mp4");


	if (!vid_in.isOpened()) {
		cout << "Error: Unable to open camera!" << endl;
	}

	while (1) {
		vid_in.read(frame);
		
		/*
		Insert your code 
		Edge detection!
		*/
		if (frame.empty()) {
			continue;
		}

		Mat gray, grad_x, grad_y, abs_grad_x, abs_grad_y, grad;

		// 1) Grayscale
		cvtColor(frame, gray, COLOR_BGR2GRAY);

		// 2) (Optional) Gaussian Blur로 노이즈 완화
		GaussianBlur(gray, gray, Size(3, 3), 0, 0, BORDER_DEFAULT);

		// 3) Sobel 미분 (X, Y)
		Sobel(gray, grad_x, ddepth, 1, 0, kernel_size, scale, delta, BORDER_DEFAULT);
		Sobel(gray, grad_y, ddepth, 0, 1, kernel_size, scale, delta, BORDER_DEFAULT);

		// 4) 절대값(8-bit)으로 변환
		convertScaleAbs(grad_x, abs_grad_x);
		convertScaleAbs(grad_y, abs_grad_y);

		// 5) X/Y를 가중합으로 결합 (엣지 강도)
		addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

		if (frame.empty()) {
			cout << "Error: Disconnection happened!" << endl;
		}

		imshow("CAM", grad);
		keychar = waitKey(5);
		if (keychar == 'c' || keychar == 'C') {
			break;
		}
	}
}