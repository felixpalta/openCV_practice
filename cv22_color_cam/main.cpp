#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

typedef enum {
	SRC_FRAME,

	R_PLANE,
	G_PLANE,
	B_PLANE,

	R_RANGED,
	G_RANGED,
	B_RANGED,
	RGB_ANDED,

	NUMBER_OF_IMAGES,
} IMAGE_NUMBERS;

typedef struct {
	const char *windowName;
	IplImage *img;
} IMG_STRUCT;

IMG_STRUCT images[NUMBER_OF_IMAGES] = {
	"original", NULL,

	"R plane", NULL,
	"G plane", NULL,
	"B plane", NULL,

	"R ranged", NULL,
	"G ranged", NULL,
	"B ranged", NULL,

	"RGB AND", NULL,
};

int Rmin,Rmax,Gmin,Gmax,Bmin,Bmax;
int RgbMax = 256;

const char *defaultName = "cat.jpg";
const char ESC = 27;
const char ENTER = 13;

void createImagesAndWindows(IplImage *);
void showAllImages();
void releaseAllImages();
void setMinMax();


void andAllPlanes(){
	cvAnd(images[R_RANGED].img,images[G_RANGED].img,images[RGB_ANDED].img);
	cvAnd(images[RGB_ANDED].img,images[B_RANGED].img,images[RGB_ANDED].img);
	cvShowImage(images[RGB_ANDED].windowName,images[RGB_ANDED].img);
}

void updatePlanes(){
	cvSplit(images[SRC_FRAME].img,images[B_PLANE].img,images[G_PLANE].img,images[R_PLANE].img,0);
}

void updateRanged(){
	IMG_STRUCT *plane = images + R_PLANE;
	IMG_STRUCT *ranged = images + R_RANGED;
	int min = Rmin;
	int max = Rmax;
	cvInRangeS(plane->img,cvScalar(min),cvScalar(max),ranged->img);
	plane = images + G_PLANE;
	ranged = images + G_RANGED;
	min = Gmin;
	max = Gmax;
	cvInRangeS(plane->img,cvScalar(min),cvScalar(max),ranged->img);
	plane = images + B_PLANE;
	ranged = images + B_RANGED;
	min = Bmin;
	max = Bmax;
	cvInRangeS(plane->img,cvScalar(min),cvScalar(max),ranged->img);
}




int main()
{
	using namespace std;
	CvCapture *capture = cvCreateCameraCapture(CV_CAP_ANY);
	
	
	if (!capture){
		cout << "Can't capture: ";
		cin.ignore();
		exit(1);
	}

	double width = cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH);
	double height = cvGetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT);

	cout << "Width: " << width << "\nHeight: " << height << endl;

	images[SRC_FRAME].img = cvQueryFrame(capture);
	assert(images[SRC_FRAME].img->depth == 8 && images[SRC_FRAME].img->nChannels == 3 );


	createImagesAndWindows(images[SRC_FRAME].img);
	setMinMax();

	
	cvCreateTrackbar("R min",images[R_RANGED].windowName,&Rmin,RgbMax);
	cvCreateTrackbar("R max",images[R_RANGED].windowName,&Rmax,RgbMax);
	cvCreateTrackbar("G min",images[G_RANGED].windowName,&Gmin,RgbMax);
	cvCreateTrackbar("G max",images[G_RANGED].windowName,&Gmax,RgbMax);
	cvCreateTrackbar("B min",images[B_RANGED].windowName,&Bmin,RgbMax);
	cvCreateTrackbar("B max",images[B_RANGED].windowName,&Bmax,RgbMax);
	showAllImages();


	const int frameDelay = 15;

	for (;;){
		images[SRC_FRAME].img = cvQueryFrame(capture);
		updatePlanes();
		
		updateRanged();
		andAllPlanes();

		showAllImages();


		if (cvWaitKey(frameDelay) == ESC)
			break;
	}

	
	
	releaseAllImages();
	
	cvDestroyAllWindows();
	
	return 0;
}

void createImagesAndWindows(IplImage *src){
	for (int i = SRC_FRAME + 1; i < NUMBER_OF_IMAGES; ++i){
		images[i].img = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
		cvNamedWindow(images[i].windowName,CV_WINDOW_AUTOSIZE);
	}
	cvDestroyWindow(images[R_PLANE].windowName);
	cvDestroyWindow(images[G_PLANE].windowName);
	cvDestroyWindow(images[B_PLANE].windowName);
}



void showAllImages(){
	cvShowImage(images[SRC_FRAME].windowName,images[SRC_FRAME].img);
	for (int i = R_RANGED; i < NUMBER_OF_IMAGES; ++i)
		cvShowImage(images[i].windowName,images[i].img);
}

void releaseAllImages(){
	for (int i = SRC_FRAME +1; i < NUMBER_OF_IMAGES; ++i) // can't release the frame, used for capturing
		cvReleaseImage(&images[i].img);
}



void setMinMax(){
	double framemin = 0;
	double framemax = 0;
	cvMinMaxLoc(images[R_PLANE].img,&framemin,&framemax);
	Rmin = (int) framemin;
	Rmax = (int) framemax;
	cvMinMaxLoc(images[G_PLANE].img,&framemin,&framemax);
	Gmin = (int) framemin;
	Gmax = (int) framemax;
	cvMinMaxLoc(images[B_PLANE].img,&framemin,&framemax);
	Bmin = (int) framemin;
	Bmax = (int) framemax;

}