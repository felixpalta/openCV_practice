#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <iostream>


const char *winName = "camera capture";
const char ESC = 27;
const char ENTER = 13;

int main()
{
	using namespace std;

	
	CvCapture *capture = cvCreateCameraCapture(CV_CAP_ANY);
	if (!capture){
		cout << "Can't access any camera." << endl;
		exit(1);
	}

	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 320);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 240);

	double width = cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH);
	double height = cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT);

	cout << "width: " << width << endl;
	cout << "height: " << height << endl;

	cvNamedWindow(winName,CV_WINDOW_AUTOSIZE);

	cout << "Press Enter for frame capture and Escape for exit" << endl;

	const char fileBegin[] = "Image";
	const char fileEnd[] = ".jpg";

	int counter = 0;

	for (;;){
		IplImage *frame = cvQueryFrame(capture);
		cvShowImage(winName,frame);
		int c = cvWaitKey(33);
		if (c == ESC)
			break;
		else if (c == ENTER){

			ostringstream ost;
			ost << fileBegin << counter << fileEnd;
			cvSaveImage(ost.str().c_str(),frame);
			cout << "captured: " << ost.str() << endl;
			++counter;			
		}
	}
	cvReleaseCapture(&capture);
	cvDestroyAllWindows();
	return 0;
}