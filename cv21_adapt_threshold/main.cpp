#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

typedef enum {
	ADAPT_THRESH_MEAN,
	ADAPT_THRESH_GAUSS,

	NUMBER_OF_METHODS,

} AdaptThreshMethods;


typedef struct {
	const char *winName;
	IplImage *img;
	int threshMethod;
} ImgAndWindow;



// all window names, images in them and corresponding thresh types packed into one variable
ImgAndWindow results[NUMBER_OF_METHODS] = {
	"Adaptive, Mean, Binary",NULL, CV_ADAPTIVE_THRESH_MEAN_C,
	"Adaptive, Gauss, Binary", NULL, CV_ADAPTIVE_THRESH_GAUSSIAN_C,
};

IplImage *src;

void createResultsAndWindows(){
	for (int i = 0; i < NUMBER_OF_METHODS;++i){
		results[i].img = cvCloneImage(src);
		cvNamedWindow(results[i].winName,CV_WINDOW_AUTOSIZE);
	}
}

void updateResults(){
	for (int i = 0; i < NUMBER_OF_METHODS;++i){
		cvShowImage(results[i].winName,results[i].img);
	}
}

void releaseResults(){
	for (int i = 0; i < NUMBER_OF_METHODS;++i){
		cvReleaseImage(&(results[i].img));
	}
}

// trackbar values, for adaptive methods
int max_value = 255;
int block_size = 3;
int param = 5;

const char *inWinName = "original";

void adaptiveTrackbarCallback(int){
	for (int i = 0; i < NUMBER_OF_METHODS;++i){
		if (block_size%2!=0 && block_size > 1)
			cvAdaptiveThreshold(src,results[i].img,max_value,results[i].threshMethod,CV_THRESH_BINARY,block_size,(double) param);
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
	
	src = cvLoadImage(filename,CV_LOAD_IMAGE_GRAYSCALE);
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
	adaptiveTrackbarCallback(0);

	cvCreateTrackbar("Max Value",inWinName,&max_value,1 << src->depth,adaptiveTrackbarCallback);
	cvCreateTrackbar("Block size",inWinName,&block_size,10,adaptiveTrackbarCallback);
	cvCreateTrackbar("Param 1",inWinName,&param,10,adaptiveTrackbarCallback);


	cvWaitKey();
	
	cvReleaseImage(&src);

	releaseResults();
	cvDestroyAllWindows();
}