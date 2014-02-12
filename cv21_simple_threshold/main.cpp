#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

typedef enum {
	BINARY,
	BINARY_INVERTED,
	TRUNC,
	TOZERO,
	TOZERO_INVERTED,
	NUMBER_OF_TYPES,

} THRESH_TYPES;


typedef struct {
	const char *winName;
	IplImage *img;
	int threshType;
} ImgAndWindow;

// all window names, images in them and corresponding thresh types packed into one variable
ImgAndWindow results[NUMBER_OF_TYPES] = {
	"binary",NULL, CV_THRESH_BINARY,
	"binary inverted", NULL, CV_THRESH_BINARY_INV,
	"truncated", NULL, CV_THRESH_TRUNC,
	"to zero", NULL, CV_THRESH_TOZERO,
	"to zero inverted", NULL, CV_THRESH_TOZERO_INV,
};

IplImage *src;

void createResultsAndWindows(){
	for (int i = 0; i < NUMBER_OF_TYPES;++i){
		results[i].img = cvCloneImage(src);
		cvNamedWindow(results[i].winName,CV_WINDOW_AUTOSIZE);
	}
}

void updateResults(){
	for (int i = 0; i < NUMBER_OF_TYPES;++i){
		cvShowImage(results[i].winName,results[i].img);
	}
}

void releaseResults(){
	for (int i = 0; i < NUMBER_OF_TYPES;++i){
		cvReleaseImage(&(results[i].img));
	}
}

int trackpos;

const char *inWinName = "original";

void thresholdTrackbarCallback(int pos){
	for (int i = 0; i < NUMBER_OF_TYPES;++i){
		cvThreshold(src,results[i].img,pos,1 << src->depth,results[i].threshType); // max value == max brightness
	}
	updateResults();
}

const char *defaultName = "bwcat.jpg";



const char ESC = 27;
const char ENTER = 13;


int main(int argc, char *argv[])
{
	using namespace std;

	const char *filename = (argc > 1) ? argv[1] : defaultName;
	
	src = cvLoadImage(filename);
	if (!src){
		cout << "Can't load image: " << filename << endl;
		cin.ignore();
		exit(1);
	}
	cout << "Image loaded: " << filename << endl;

	cvNamedWindow(inWinName,CV_WINDOW_AUTOSIZE);
	cvShowImage(inWinName,src);

	createResultsAndWindows();
	updateResults();

	cvCreateTrackbar("Threshold",inWinName,&trackpos,1 << src->depth,thresholdTrackbarCallback);

	cvWaitKey();
	
	cvReleaseImage(&src);
	releaseResults();
	cvDestroyAllWindows();
}