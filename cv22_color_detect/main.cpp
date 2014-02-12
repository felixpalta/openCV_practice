#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

typedef enum {
	SRC_FIRST,

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

void redTrackbar(int){
	IMG_STRUCT *plane = images + R_PLANE;
	IMG_STRUCT *ranged = images + R_RANGED;
	int min = Rmin;
	int max = Rmax;
	cvInRangeS(plane->img,cvScalar(min),cvScalar(max),ranged->img);
	cvShowImage(ranged->windowName,ranged->img);
	andAllPlanes();
	
}

void greenTrackbar(int){
	IMG_STRUCT *plane = images + G_PLANE;
	IMG_STRUCT *ranged = images + G_RANGED;
	int min = Gmin;
	int max = Gmax;
	cvInRangeS(plane->img,cvScalar(min),cvScalar(max),ranged->img);
	cvShowImage(ranged->windowName,ranged->img);
	andAllPlanes();
}

void blueTrackbar(int){
	IMG_STRUCT *plane = images + B_PLANE;
	IMG_STRUCT *ranged = images + B_RANGED;
	int min = Bmin;
	int max = Bmax;
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

	
	cvCreateTrackbar("R min",images[R_RANGED].windowName,&Rmin,RgbMax,redTrackbar);
	cvCreateTrackbar("R max",images[R_RANGED].windowName,&Rmax,RgbMax,redTrackbar);
	cvCreateTrackbar("G min",images[G_RANGED].windowName,&Gmin,RgbMax,greenTrackbar);
	cvCreateTrackbar("G max",images[G_RANGED].windowName,&Gmax,RgbMax,greenTrackbar);
	cvCreateTrackbar("B min",images[B_RANGED].windowName,&Bmin,RgbMax,blueTrackbar);
	cvCreateTrackbar("B max",images[B_RANGED].windowName,&Bmax,RgbMax,blueTrackbar);
	showAllImages();

	redTrackbar(0);
	greenTrackbar(0);
	blueTrackbar(0);

	cvWaitKey();
	
	releaseAllImages();
	
	cvDestroyAllWindows();
}

void createImagesAndWindows(IplImage *src){
	for (int i = SRC_FIRST + 1; i < NUMBER_OF_IMAGES; ++i){
		images[i].img = cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
		cvNamedWindow(images[i].windowName,CV_WINDOW_AUTOSIZE);
	}
	cvSplit(src,images[B_PLANE].img,images[G_PLANE].img,images[R_PLANE].img,0);
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