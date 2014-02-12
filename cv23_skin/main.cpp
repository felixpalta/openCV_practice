#include <cv.h>
#include <highgui.h>
#include <cvaux.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

const char *inWinName = "original";
const char *outWinName = "result";
const char *maskWindow = "mask";

const char *defaultName = "cat.png";
const char ESC = 27;
const char ENTER = 13;

int main(int argc, char *argv[])
{
	using namespace std;
	const char *filename = (argc > 1) ? argv[1] : defaultName;
	
	IplImage *src = cvLoadImage(filename);
	if (!src){
		cout << "Can't load image: " << filename << endl;
		cin.ignore();
		exit(1);
	}
	cout << "Image loaded: " << filename << endl;

	cvNamedWindow(inWinName,CV_WINDOW_AUTOSIZE);
	cvShowImage(inWinName,src);

	IplImage *dst = cvCloneImage(src);
	IplImage *mask = cvCreateImage(cvGetSize(src),8,1);

	CvAdaptiveSkinDetector mySkinFilter(1,CvAdaptiveSkinDetector::MORPHING_METHOD_ERODE_ERODE);
	mySkinFilter.process(src,mask);

	

	for( int y=0; y<dst->height; y++ ) {
		for( int x=0; x<dst->width; x++ ) {
			
			if ((int)cvGetReal2D(mask,y,x)){
				CvScalar s = cvGet2D(dst,y,x);
				s.val[1] = 255;
				cvSet2D(dst,y,x,s);
				cvSetReal2D(mask,y,x,255);
			}
				
		}
	}
	cvShowImage(maskWindow,mask);
	cvShowImage(outWinName,dst);

	cvWaitKey();
	
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	cvReleaseImage(&mask);

	
	cvDestroyAllWindows();
}