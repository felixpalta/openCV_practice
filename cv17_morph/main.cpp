#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

const char *inWinName = "original";
const char *erodeWin = "erode";
const char *dilateWin = "dilate";
const char *defaultName = "cat.jpg";
const char ESC = 27;
const char ENTER = 13;


// data structure to pass to trackbar callbacks
typedef struct {
	IplImage *srcimg;
	IplImage *erodeimg;
	IplImage *dilateimg;
} TrackbarData;

// trackbar variables and callbacks
int radius = 1;
int iterations = 1;

void updateImages(TrackbarData * data){
	int width,height;
	width = height = 2*radius +1;
	IplConvKernel *Kern = cvCreateStructuringElementEx(width,height,radius,radius,CV_SHAPE_ELLIPSE);

	IplImage *src = data->srcimg;
	IplImage *erode = data->erodeimg;
	IplImage *dilate = data->dilateimg;

	cvErode(src,erode,Kern,iterations);
	cvDilate(src,dilate,Kern,iterations);

	cvShowImage(erodeWin,erode);
	cvShowImage(dilateWin,dilate);

	cvReleaseStructuringElement(&Kern);
}

void bothTrackbarsCallback(int,void *data){
	updateImages((TrackbarData*)data);
}

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
	IplImage *erode = cvCloneImage(src);
	IplImage *dilate = cvCloneImage(src);
	cvNamedWindow(erodeWin,CV_WINDOW_AUTOSIZE);
	cvNamedWindow(dilateWin,CV_WINDOW_AUTOSIZE);
	cvShowImage(erodeWin,erode);
	cvShowImage(dilateWin,dilate);

	TrackbarData data = {
		src,
		erode,
		dilate,
	};
	const int rad_max = 10;
	cvCreateTrackbar2("Radius",inWinName,&radius,rad_max,bothTrackbarsCallback,&data);
	const int iter_max = 10;
	cvCreateTrackbar2("Iterations",inWinName,&iterations,iter_max,bothTrackbarsCallback,&data);

	cvWaitKey();	// images will be updated on trackbars change

	cvReleaseImage(&src);
	cvReleaseImage(&erode);
	cvReleaseImage(&dilate);


	cvDestroyAllWindows();
}