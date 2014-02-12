#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <videoInput.h>

const char *inWinName = "original";
const char *outWinName = "result";
const char *defaultName = "cat.jpg";
const char ESC = 27;
const char ENTER = 13;

int xorder = 1, yorder  = 1; // trackbar variables
int xorder_max = 2, yorder_max = 2;
int aperture = 3, aperture_max = 7;

IplImage *src,*dst,*dst2;

int getUnevenAperture(){
	if (aperture%2 == 0)
		return aperture-1;
	return aperture;
}

void allTrackbarsCallback(int){
	if (xorder !=0 || yorder !=0){
		int ap = getUnevenAperture();
		if (ap == CV_SCHARR)
		{
			if ((xorder == 0 && yorder ==1) || (xorder == 1 && yorder == 0))
				cvSobel(src,dst,xorder,yorder,ap);
			else
				std::cout << "Scharr can be used only for the first dx or dy derivative " << std::endl;
		}
		else
			cvSobel(src,dst,xorder,yorder,ap);

		
		cvScale(dst,dst2);
		cvShowImage(outWinName,dst2);
		return;
	}
	std::cout << "Both dx and dy set to zero" << std::endl;
}

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
	
	dst = cvCreateImage(cvGetSize(src),IPL_DEPTH_16S,src->nChannels);
	dst2 = cvCloneImage(src);
	
	cvCreateTrackbar("X order",inWinName,&xorder,xorder_max,allTrackbarsCallback);
	cvCreateTrackbar("Y order",inWinName,&yorder,yorder_max,allTrackbarsCallback);
	cvCreateTrackbar("Aperture",inWinName,&aperture,aperture_max,allTrackbarsCallback);

	allTrackbarsCallback(0);

	cvWaitKey();
		
	cvReleaseImage(&src);
	
	cvDestroyAllWindows();
}