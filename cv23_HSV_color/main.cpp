#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

typedef enum {
	SRC_FIRST,

	HSV_SRC,

	H_PLANE,
	S_PLANE,
	V_PLANE,

	H_RANGED,
	S_RANGED,
	V_RANGED,
	HSV_ANDED,

	NUMBER_OF_IMAGES,
} IMAGE_NUMBERS;

typedef struct {
	const char *windowName;
	IplImage *img;
} IMG_STRUCT;

IMG_STRUCT images[NUMBER_OF_IMAGES] = {
	"original", NULL,

	"HSV original", NULL,

	"H plane", NULL,
	"S plane", NULL,
	"V plane", NULL,

	"H ranged", NULL,
	"S ranged", NULL,
	"V ranged", NULL,

	"HSV AND", NULL,
};

int Hmin,Hmax,Smin,Smax,Vmin,Vmax;
int HsvMax = 256;

const char *defaultName = "cat.jpg";
const char ESC = 27;
const char ENTER = 13;

void createImagesAndWindows(IplImage *);
void showAllImages();
void releaseAllImages();
void setMinMax();


void andAllPlanes(){
	cvAnd(images[H_RANGED].img,images[S_RANGED].img,images[HSV_ANDED].img);
	cvAnd(images[HSV_ANDED].img,images[V_RANGED].img,images[HSV_ANDED].img);
	cvShowImage(images[HSV_ANDED].windowName,images[HSV_ANDED].img);
}

void hueTrackbar(int){
	IMG_STRUCT *plane = images + H_PLANE;
	IMG_STRUCT *ranged = images + H_RANGED;
	int min = Hmin;
	int max = Hmax;
	cvInRangeS(plane->img,cvScalar(min),cvScalar(max),ranged->img);
	cvShowImage(ranged->windowName,ranged->img);
	andAllPlanes();
	
}

void saturationTrackbar(int){
	IMG_STRUCT *plane = images + S_PLANE;
	IMG_STRUCT *ranged = images + S_RANGED;
	int min = Smin;
	int max = Smax;
	cvInRangeS(plane->img,cvScalar(min),cvScalar(max),ranged->img);
	cvShowImage(ranged->windowName,ranged->img);
	andAllPlanes();
}

void valueTrackbar(int){
	IMG_STRUCT *plane = images + V_PLANE;
	IMG_STRUCT *ranged = images + V_RANGED;
	int min = Vmin;
	int max = Vmax;
	cvInRangeS(plane->img,cvScalar(min),cvScalar(max),ranged->img);
	cvShowImage(ranged->windowName,ranged->img);
	andAllPlanes();
}


int main(int argc, char *argv[])
{
	using namespace std;
	const char *filename = (argc > 1) ? argv[1] : defaultName;
	
	IplImage *srcPtr = cvLoadImage(filename,CV_LOAD_IMAGE_UNCHANGED);
	if (!srcPtr){
		cout << "Can't load image: " << filename << endl;
		cin.ignore();
		exit(1);
	}
	images[SRC_FIRST].img = srcPtr;
	assert(srcPtr->depth == 8 && srcPtr->nChannels == 3 );
	cout << "Image loaded: " << filename << endl;

	createImagesAndWindows(srcPtr);
	setMinMax();

	
	cvCreateTrackbar("H min",images[H_RANGED].windowName,&Hmin,HsvMax,hueTrackbar);
	cvCreateTrackbar("H max",images[H_RANGED].windowName,&Hmax,HsvMax,hueTrackbar);
	cvCreateTrackbar("S min",images[S_RANGED].windowName,&Smin,HsvMax,saturationTrackbar);
	cvCreateTrackbar("S max",images[S_RANGED].windowName,&Smax,HsvMax,saturationTrackbar);
	cvCreateTrackbar("V min",images[V_RANGED].windowName,&Vmin,HsvMax,valueTrackbar);
	cvCreateTrackbar("V max",images[V_RANGED].windowName,&Vmax,HsvMax,valueTrackbar);
	showAllImages();

	hueTrackbar(0);
	saturationTrackbar(0);
	valueTrackbar(0);

	cvWaitKey();
	
	releaseAllImages();
	
	cvDestroyAllWindows();
}

void createImagesAndWindows(IplImage *src){
	images[HSV_SRC].img = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,3); // 3 channel HSV source image
	for (int i = HSV_SRC + 1; i < NUMBER_OF_IMAGES; ++i){
		images[i].img = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
		cvNamedWindow(images[i].windowName,CV_WINDOW_AUTOSIZE);
	}
	cvCvtColor(src,images[HSV_SRC].img,CV_BGR2HSV);
	
	cvSplit(src,images[H_PLANE].img,images[S_PLANE].img,images[V_PLANE].img,0); // same as cvCvtPixToPlane
}

void showAllImages(){
	for (int i = 0; i < NUMBER_OF_IMAGES; ++i)
		cvShowImage(images[i].windowName,images[i].img);
}

void releaseAllImages(){
	for (int i = 0; i < NUMBER_OF_IMAGES; ++i)
		cvReleaseImage(&images[i].img);
}

void setMinMax(){
	double framemin = 0;
	double framemax = 0;
	cvMinMaxLoc(images[H_PLANE].img,&framemin,&framemax);
	Hmin = (int) framemin;
	Hmax = (int) framemax;
	cvMinMaxLoc(images[S_PLANE].img,&framemin,&framemax);
	Smin = (int) framemin;
	Smax = (int) framemax;
	cvMinMaxLoc(images[V_PLANE].img,&framemin,&framemax);
	Vmin = (int) framemin;
	Vmax = (int) framemax;

}