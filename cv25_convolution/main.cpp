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

void setKernel(CvMat* kern){
	cvSetReal2D(kern,0,0,-0.1);	cvSetReal2D(kern,0,1,.2);	cvSetReal2D(kern,0,2,-0.1);

	cvSetReal2D(kern,1,0,.2);	cvSetReal2D(kern,1,1,3);	cvSetReal2D(kern,1,2,.2);

	cvSetReal2D(kern,2,0,-0.1);	cvSetReal2D(kern,2,1,.2);	cvSetReal2D(kern,2,2,-0.1);
}

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

	cvNamedWindow(inWinName,CV_WINDOW_AUTOSIZE);
	cvShowImage(inWinName,src);

	IplImage *dst = cvCloneImage(src);

	CvMat *kern = cvCreateMat(3,3,CV_32FC1);

	setKernel(kern);

	for (int i = 0; i < kern->rows; ++i){
			for (int j = 0; j < kern->cols; ++j)
				cout << cvGetReal2D(kern,i,j) << '\t';
			cout << endl;
		}
	
	cvFilter2D(src,dst,kern,cvPoint(-1,-1));

	cvShowImage("result",dst);

	IplImage *big = cvCreateImage(cvSize(src->width + 20,src->height+20),8,3);
	cvCopyMakeBorder(src,big,cvPoint(10,10),IPL_BORDER_REPLICATE,cvScalar(255));
	cvShowImage("bigger image",big);


	cvWaitKey();
		
	cvReleaseImage(&src);
	cvReleaseMat(&kern);
	
	cvDestroyAllWindows();
}