#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

const char ESC = 27;

int main()
{
	using namespace std;
	const char *winName = "capture";
	cvNamedWindow(winName);
	
	CvCapture *capture = cvCreateCameraCapture(CV_CAP_ANY);
	if (!capture){
		cout << "No capture device available" << endl;
		exit(1);
	}

	const char *filename = "capture.avi";
	
	// video will be recorded, and then played with this fps
	// it can be different from fps when capturing
	//double fps = 30; 
	double fps = cvGetCaptureProperty(capture,CV_CAP_PROP_FPS);
	if ((int) fps == 0)
		fps = 15;
	int waitDelay = 1000/(int) fps;

	CvSize size = cvSize(
		(int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH),
		(int)cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT));

	CvVideoWriter *writer = cvCreateVideoWriter(filename,CV_FOURCC('F','L','V','1'),fps,size,1); // or 1
	if (!writer){
		cout << "Can't create video writer" << endl;
		exit(2);
	}

	IplImage *frame = NULL;

	for (;;){
		
		frame = cvQueryFrame(capture);
		if (!frame) {
			cout << "Can't query frame" << endl;
			break;
		}
		else {
			cvWriteFrame(writer,frame);
			cvShowImage(winName,frame);
		}
		if (cvWaitKey(waitDelay) == ESC)
			break;
	}

	
	cvReleaseCapture(&capture);
	cvReleaseVideoWriter(&writer);
	cvDestroyAllWindows();
	return 0;

}