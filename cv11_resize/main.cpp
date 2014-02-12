#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

const char *inWinName = "original";
const char *outWinName = "result";
const char *defaultName = "cat.jpg";
const char ESC = 27;
const char ENTER = 13;

double scale = 1.5;

int main(int argc, char *argv[])
{
	using namespace std;
	const char *filename = (argc > 1) ? argv[1] : defaultName;
	
	IplImage *src = cvLoadImage(filename);

	IplImage *dst[4];

	if (!src){
		cout << "Can't load image: " << filename << endl;
		cin.ignore();
		exit(1);
	}
	cout << "Image loaded: " << filename << endl;

	cvNamedWindow(inWinName,CV_WINDOW_AUTOSIZE);
	cvShowImage(inWinName,src);

	for (int i = 0; i < 4; ++i){
		dst[i] = cvCreateImage(cvSize(src->width*scale,src->height*scale),src->depth,src->nChannels);
		cvResize(src,dst[i],i);
		ostringstream ost;
		ost << "Mode: " << i;
		cvShowImage(ost.str().c_str(),dst[i]);
	}
	cvWaitKey();
	
	cvReleaseImage(&src);
	for (int i = 0; i < 4; ++i)
		cvReleaseImage(&dst[i]);
	
	cvDestroyAllWindows();
}