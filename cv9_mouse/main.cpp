#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

// callback of a mouse event, draws a target on the image passed to it.
//event, x,y and flags are passed automatically, 'param' is a user-defined data
void myMouseCallback(int event,int x, int y, int flags, void *param);

const char *default_file = "cat.jpg";
const char *winName = "target";
const char ESC = 27;

// structure to pass to mouseCallback as a user-defined data
typedef struct ImgAndWindow {
	IplImage *img;
	const char *window; // window name
} ImgAndWindow;

int main(int argc, char *argv[])
{
	using namespace std;
	const char *filename = (argc > 1) ? argv[1] : default_file;
	
	IplImage *img = cvLoadImage(filename,1);
	if (!img){
		cout << "Image not found: " << filename << endl;
		cin.ignore();
		exit(1);
	}
	cout << "Loaded image: " << filename << endl;
	
	cvNamedWindow(winName,CV_WINDOW_AUTOSIZE);

	ImgAndWindow iaw = {
		img,winName,
	};

	cvSetMouseCallback(winName,myMouseCallback,(void *)&iaw); // passing both image and window name to the callback function
	
	cvShowImage(winName,img); // otherwise the window won't show until the first event (click)
	cout << "Ctrl+Shift+click on the image to place circles" << endl;

	cvWaitKey();
	cvSaveImage("updatedcat.jpg",img);
	cvReleaseImage(&img);

	cvDestroyAllWindows();
}

void myMouseCallback(int event,int x, int y, int flags, void *param){

	void drawTarget(IplImage *img, int x, int y);
	using namespace std;

	// extracting image pointer and window name from param
	IplImage *image = (*(ImgAndWindow *)param).img;
	const char *window = (*(ImgAndWindow *)param).window;

	switch (event){
	case CV_EVENT_LBUTTONDOWN:

		if (flags & CV_EVENT_FLAG_SHIFTKEY && flags & CV_EVENT_FLAG_CTRLKEY){
			drawTarget(image,x,y);
			cvShowImage(window,image);
			cout << "x: " << x << ",\ty: " << y << endl;
		}

		break;
	default:
		break;
	}

	return;
}

void drawTarget(IplImage *img, int x, int y){
	static const int radius = 20;
	static const int thickness = 3;
	static const int linetype = CV_AA; // smooth line
	static const int shift = 0; // i have no idea, default value here
	cvCircle(img,cvPoint(x,y),radius,CV_RGB(255,0,0),thickness,linetype,shift); 

}