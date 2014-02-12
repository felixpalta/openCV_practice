#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

const char *inWinName = "original";
const char *outWinName = "result";
const char *defaultName = "cat.png";
const char ESC = 27;
const char ENTER = 13;

IplImage *srcImg;
IplImage *mask;

void fill(IplImage *src,CvPoint seed, CvScalar color = CV_RGB(255,0,0)){
	using namespace std;
	CvConnectedComp comp;

	if (mask == NULL)
		cout << "NULL Mask pointer" << endl;

	cvFloodFill(src,seed,color,cvScalarAll(10),cvScalarAll(10),&comp,4 | CV_FLOODFILL_FIXED_RANGE|CV_FLOODFILL_MASK_ONLY,mask);
	cout << "Fill area: " << comp.area << endl;
}

void myMouseCallback(int event, int x, int y, int, void *data){
	using namespace std;

	IplImage *img = (IplImage *) data;

	switch (event){
	case CV_EVENT_LBUTTONDOWN:
		cout << x << '\t' << y << endl;
		fill(img,cvPoint(x,y));
		cvShowImage(inWinName,img);
		cvShowImage(outWinName,mask);
		return;

	default:
		return;
	}
}

int main(int argc, char *argv[])
{
	using namespace std;
	const char *filename = (argc > 1) ? argv[1] : defaultName;
	
	srcImg = cvLoadImage(filename);
	if (!srcImg){
		cout << "Can't load image: " << filename << endl;
		cin.ignore();
		exit(1);
	}
	cout << "Image loaded: " << filename << endl;
	
	mask = cvCreateImage(cvSize(srcImg->width +2,srcImg->height +2),srcImg->depth,srcImg->nChannels);

	cvNamedWindow(inWinName,CV_WINDOW_AUTOSIZE);
	cvShowImage(inWinName,srcImg);
	cvNamedWindow(outWinName,CV_WINDOW_AUTOSIZE);
	cvShowImage(outWinName,mask);

	cvSetMouseCallback(inWinName,myMouseCallback,(void *)srcImg);

	cvWaitKey();
	
	cvReleaseImage(&srcImg);
	cvReleaseImage(&mask);
	
	cvDestroyAllWindows();
}