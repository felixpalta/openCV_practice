#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

const char *bigWindow = "first img";
const char *smallWindow = "second img";
const char *resultWindow = "result";

const char *bigName = "bigcat.jpg";
const char *smallName = "smallcat.jpg";

const char ESC = 27;
const char ENTER = 13;

int main(int argc, char *argv[])
{
	using namespace std;
	const char *bigFile = (argc > 1) ? argv[1] : bigName;
	const char *smallFile = (argc > 2) ? argv[2] : smallName;

	IplImage *bigImg = cvLoadImage(bigFile);
	if (!bigImg){
		cout << "Can't load image: " << bigFile << endl;
		cin.ignore();
		exit(1);
	}
	cout << "Image loaded: " << bigFile << endl;

	IplImage *smallImg = cvLoadImage(smallFile);
	if (!smallImg){
		cout << "Can't load image: " << smallFile << endl;
		cin.ignore();
		exit(2);
	}
	cout << "Image loaded: " << smallFile << endl;

	if (smallImg->width > bigImg->width || smallImg->height > bigImg->height){
		cout << "Error: " << smallFile << " is bigger than " << bigFile << endl;
		cin.ignore();
		exit (3);
	}

	cvSetImageROI(bigImg,cvRect(0,0,smallImg->width,smallImg->height));

	IplImage *dst = cvCloneImage(smallImg);

	double alpha = .5;
	double beta = .5;
	double gamma = 100;

	cvAddWeighted(bigImg,alpha,smallImg,beta,gamma,dst);

	cvResetImageROI(bigImg);

	cvNamedWindow(bigWindow,CV_WINDOW_AUTOSIZE);
	cvShowImage(bigWindow,bigImg);

	cvNamedWindow(smallWindow,CV_WINDOW_AUTOSIZE);
	cvShowImage(smallWindow,smallImg);

	cvNamedWindow(resultWindow,CV_WINDOW_AUTOSIZE);
	cvShowImage(resultWindow,dst);

	cvWaitKey();
	
	cvReleaseImage(&bigImg);
	cvReleaseImage(&smallImg);
	cvReleaseImage(&dst);
	
	cvDestroyAllWindows();
}