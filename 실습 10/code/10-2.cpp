#include <opencv2/opencv.hpp>
#include <iostream>
#include "lab10.h"

using namespace cv;
using namespace std;

int main2() {
	char keychar;
	Mat frame;
	VideoCapture vid_in = VideoCapture("sample.mp4");

	if (vid_in.isOpened())
	{
		cout << "Error: Unable to open camera!" << endl;
	}

	while (1)
	{
		vid_in.read(frame);
		if (frame.empty())
		{
			cout << "Error: Disconnection happened!" << endl;
		}
		imshow("CAM", frame);
		keychar = waitKey(5);
		if (keychar == 'c' || keychar == 'C')
		{
			break;
		}
	}

	return 0;
}
