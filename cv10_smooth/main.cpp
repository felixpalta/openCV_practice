#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

const char *inWinName = "original";
const char *gaussWindow = "gauss";
const char *blurWindow = "blur";
const char *blurNoScaleWindow = "blur no scale";

const char *defaultName = "cat.jpg";

IplImage *src;

void gaussCallback(int pos, void * dst){
	if (pos != 0){
		cvSmooth(src,(IplImage *)dst,CV_GAUSSIAN,pos,pos);
		cvShowImage(gaussWindow,dst);
	}
}

void blurCallback(int pos, void * dst){
	if (pos != 0){
		cvSmooth(src,(IplImage *)dst,CV_BLUR,pos,pos);
		cvShowImage(blurWindow,dst);
	}
}

void blurNoScaleCallback(int pos, void * dst){
	if (pos != 0){
		cvSmooth(src,(IplImage *)dst,CV_BLUR_NO_SCALE,pos,pos);
		cvShowImage(blurNoScaleWindow,dst);
	}
}

int main(int argc, char *argv[])
{
	using namespace std;
	const char *filename = (argc >1) ? argv[1]:defaultName;
	
	src = cvLoadImage(filename);
	if (!src){
		cout << "Can't load image: " << filename << endl;
		cin.ignore();
		exit(1);
	}
	cout << "Image loaded: " << filename << endl;
	IplImage *gaussDst = cvCloneImage(src);
	IplImage *blurDst = cvCloneImage(src);
	IplImage *blurNoScaleDst = cvCloneImage(src);

	cvNamedWindow(inWinName,CV_WINDOW_AUTOSIZE);
	cvNamedWindow(gaussWindow,CV_WINDOW_AUTOSIZE);
	cvNamedWindow(blurWindow,CV_WINDOW_AUTOSIZE);
	cvNamedWindow(blurNoScaleWindow,CV_WINDOW_AUTOSIZE);

	int gaussSize = 1;
	cvCreateTrackbar2("Gaussian",gaussWindow,&gaussSize,10,gaussCallback,(void *)gaussDst);
	int blurSize = 1;
	cvCreateTrackbar2("Blur",blurWindow,&blurSize,10,blurCallback,(void *)blurDst);
	int blurNoScaleSize = 1;
	cvCreateTrackbar2("Blur, No",blurNoScaleWindow,&blurNoScaleSize,10,blurNoScaleCallback,(void *)blurNoScaleDst);


	cvShowImage(inWinName,src);
	cvShowImage(gaussWindow,src);
	cvShowImage(blurWindow,src);
	cvShowImage(blurNoScaleWindow,src);

	cvWaitKey();
	cvReleaseImage(&src);
	cvReleaseImage(&gaussDst);
	cvReleaseImage(&blurDst);
	cvReleaseImage(&blurNoScaleDst);
	cvDestroyAllWindows();
}