#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

const char *inWinName = "original";
const char *openWin = "open";
const char *closeWin = "close";
const char *gradientWin = "gradient";
const char *blackhatWin = "blackhat";
const char *tophatWin = "tophat";

IplImage *srcImg,*openImg,*closeImg, *gradientImg, *blackhatImg, *tophatImg;

const char *defaultName = "cat.png";
const char ESC = 27;
const char ENTER = 13;



// trackbar variables and callbacks
int radius = 1;
int iterations = 1;

void bothTrackbarsCallback(int){
	int width,height;
	width = height = 2*radius +1;
	IplConvKernel *Kern = cvCreateStructuringElementEx(width,height,radius,radius,CV_SHAPE_ELLIPSE);

// 	IplImage* Temp = 0;
// 	Temp = cvCreateImage(cvSize(srcImg->width, srcImg->height) , IPL_DEPTH_8U, 1);

	// using output image as temp
	cvMorphologyEx(srcImg, openImg, openImg, Kern, CV_MOP_OPEN, iterations); 
	cvMorphologyEx(srcImg, closeImg, closeImg, Kern, CV_MOP_CLOSE, iterations);
	cvMorphologyEx(srcImg, gradientImg, gradientImg, Kern, CV_MOP_GRADIENT, iterations);
	cvMorphologyEx(srcImg, tophatImg, tophatImg, Kern, CV_MOP_TOPHAT, iterations);
	cvMorphologyEx(srcImg, blackhatImg, blackhatImg, Kern, CV_MOP_BLACKHAT, iterations);

	cvShowImage(openWin,openImg);
	cvShowImage(closeWin,closeImg);
	cvShowImage(gradientWin,gradientImg);
	cvShowImage(blackhatWin,blackhatImg);
	cvShowImage(tophatWin,tophatImg);

	cvReleaseStructuringElement(&Kern);
	//cvReleaseImage(&Temp);
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

	cvNamedWindow(inWinName,CV_WINDOW_AUTOSIZE);
	cvShowImage(inWinName,srcImg);
	openImg = cvCloneImage(srcImg);
	closeImg = cvCloneImage(srcImg);
	gradientImg = cvCloneImage(srcImg);
	tophatImg = cvCloneImage(srcImg);
	blackhatImg = cvCloneImage(srcImg);

	cvNamedWindow(openWin,CV_WINDOW_AUTOSIZE);
	cvNamedWindow(closeWin,CV_WINDOW_AUTOSIZE);
	cvNamedWindow(gradientWin,CV_WINDOW_AUTOSIZE);
	cvNamedWindow(tophatWin,CV_WINDOW_AUTOSIZE);
	cvNamedWindow(blackhatWin,CV_WINDOW_AUTOSIZE);
	cvShowImage(openWin,openImg);
	cvShowImage(closeWin,closeImg);
	cvShowImage(gradientWin,gradientImg);
	cvShowImage(blackhatWin,blackhatImg);
	cvShowImage(tophatWin,tophatImg);


	const int rad_max = 10;
	cvCreateTrackbar("Radius",inWinName,&radius,rad_max,bothTrackbarsCallback);
	const int iter_max = 10;
	cvCreateTrackbar("Iterations",inWinName,&iterations,iter_max,bothTrackbarsCallback);

	cvWaitKey();	// images will be updated on trackbars change

	cvReleaseImage(&srcImg);
	cvReleaseImage(&openImg);
	cvReleaseImage(&closeImg);


	cvDestroyAllWindows();
}