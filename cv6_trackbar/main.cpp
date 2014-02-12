#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

const char *winName = "capture";
const char ESC = 27;

void myTrackbarCallback(int pos,void *cap){
	
	
	cvSetCaptureProperty((CvCapture *)cap,CV_CAP_PROP_POS_FRAMES,pos);
}

int main(int argc, char* argv[])
{
	using namespace std;

	char *filename = (argc == 2 ? argv[1] : "test.avi");

	CvCapture *capture = cvCreateFileCapture(filename);

	if (capture == NULL){
		cout << "File not found: " << filename << endl;
		exit(1);
	}
	cout << "Loaded file: " << filename << endl;

	cvNamedWindow(winName,CV_WINDOW_AUTOSIZE);

	double framesCount = cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_COUNT);
	cout << "Frames in the capture: " << framesCount << endl;
	int frames = (int) framesCount;
	int position = 0;

	if (frames!= 0) {
		cvCreateTrackbar2("Position",winName,&position,frames,myTrackbarCallback,capture);
	}

	for (;;){
		IplImage *frame = cvQueryFrame(capture);
		if (!frame){
			cout << "Out of frames" << endl;
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