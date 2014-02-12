#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

void myMouseCallback(int event,int x, int y, int,void *data);

const char *inWinName = "original";
const char *outWinName = "result";
const char *defaultName = "cat.jpg";
const char *addName = "eye.jpg";
const char ESC = 27;
const char ENTER = 13;

// data structure to be passed to myMouseCallback
typedef struct MouseData {
	IplImage *img;
	const char *window;
} MouseData;



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

	IplImage *addImage = cvLoadImage(addName);
	if (!addImage){
		cout << "Can't load image: " << addName << endl;
		cin.ignore();
		exit(1);
	}
	// adding one image to another
	cvSetImageROI(src,cvRect(200,100,addImage->width,addImage->height));
	
	cvZero(src); // not really necessary before copying
	cvCopyImage(addImage,src);
	
	cvResetImageROI(src); // is needed before call to cvShowImage

	cvNamedWindow(inWinName,CV_WINDOW_AUTOSIZE);
	cvShowImage(inWinName,src);

	static MouseData data = {
		src, inWinName,
	};

	cvSetMouseCallback(inWinName,myMouseCallback,(void *) &data);
	cout << "Click on image twice, to form a rectangular ROI and add a scalar to it" << endl;
	// and now image will be updated only in myMouseCallback

	cvWaitKey();
	
	cvReleaseImage(&src);
	cvReleaseImage(&addImage);
	
	cvDestroyAllWindows();
}
/*
This callback reacts after two clicks, that form ROI.
After second click it adds a scalar to that ROI
*/
void myMouseCallback(int event,int x, int y, int,void *data){
	using namespace std;

	IplImage *img = ((MouseData *)data)->img;
	const char *window = ((MouseData *)data)->window;
	static bool secondClick = false; 
	static int old_x,old_y;

	switch (event){
	case CV_EVENT_LBUTTONDOWN:
		cout << "x: " << x << "\ty: " << y << endl;
		if (secondClick){
			int width = abs(x - old_x);
			int height = abs(y - old_y);
			int x_origin = min(x,old_x);
			int y_origin = min(y,old_y);
			cvSetImageROI(img,cvRect(x_origin,y_origin,width,height));
			cvAddS(img,cvScalar(0,255,0),img); // scalar is (BLUE,GREEN,RED)
			cvResetImageROI(img);
			cvShowImage(window,img);
			secondClick = false;
			return;
		}
		secondClick = true;
		old_x = x;
		old_y = y;
		break;
	default:
		break;
	}
}