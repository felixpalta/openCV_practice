#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int height	= 640;
	int width	= 480;
	int depth = 8;
	int nchannels = 3;
	/*
	creating image, 
	with 'depth' bit
	 and 'nchannels' channels of each color
	IplImage casts to CvArr without prompt
	*/
	IplImage *img = cvCreateImage(cvSize(width,height),depth,nchannels);
	// filling image with color (black)
	cvSet(img,cvScalar(0,0,0));

	CvFont font;
	cvInitFont(&font,CV_FONT_HERSHEY_COMPLEX,1.0,1.0,0,1,CV_AA); // i have no idea

	// origin of the  text
	CvPoint pt = cvPoint(width/4,height/2);

	cvPutText(img,"hello opencv",pt,&font,CV_RGB(0xFF,0,0));

	char *winName = "takie dela";
	cvNamedWindow(winName,CV_WINDOW_AUTOSIZE);
	cvMoveWindow(winName,860,540);
	cvShowImage(winName,img);
	cvWaitKey();

	cvReleaseImage(&img);
	cvDestroyWindow(winName);
	return 0;
}