#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <videoInput.h>


const char ESC = 27;
const char ENTER = 13;

int main()
{
	using namespace std;

	videoInput VI;

	int numDevices = VI.listDevices();
	assert(numDevices != 0);
	int device1 = 0;

	VI.setIdealFramerate(device1,15);
	
	VI.setupDevice(device1,320,240,VI_COMPOSITE);

	IplImage *img = cvCreateImage(cvSize(VI.getWidth(device1),VI.getHeight(device1)),8,3);

	for(;;){
		if (VI.isFrameNew(device1)) {
			VI.getPixels(device1,(unsigned char *)img->imageData,false,true);
			cvShowImage("capture",img);
		}
		if (cvWaitKey(1) == ESC)
			break;
	}
	cvReleaseImage(&img);
	
	cvDestroyAllWindows();
}