#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

const char *winName = "capture";
const char ESC = 27;

int main(int argc, char* argv[])
{
	using namespace std;

	char *filename = (argc == 2 ? argv[1] : "test.avi");

	CvCapture *capture = cvCreateFileCapture(filename);

	if (capture == NULL){
		cout << "File not found: " << filename << endl;
		exit(1);
	}
	cvNamedWindow(winName,CV_WINDOW_AUTOSIZE);
	for (;;){
		IplImage *frame = cvQueryFrame(capture);
		if (!frame){
			cout << "Can't capture a frame" << endl;
			break;
		}
		cvShowImage(winName,frame);
		int c = cvWaitKey(15); // for 30 FPS
		if (c == ESC)
			break;
	}

	cvReleaseCapture(&capture);
	cvDestroyAllWindows();
	
}