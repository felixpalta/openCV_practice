#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <iostream>

int main(int argc,char *argv[])
{
	char *filename = (argc == 2 ? argv[1]: "Image0.jpg");
	using namespace std;
	IplImage *orig = cvLoadImage(filename,CV_LOAD_IMAGE_GRAYSCALE);
	if (orig == NULL){
		cout << "File not found, aborting..." << endl;
		getchar();
		exit(1);
	}
	cout << "image loaded: " << filename << endl;

	IplImage *copy = cvCloneImage(orig);
	
	cvShowImage("original",orig);
	cout << "channels:\t" << orig->nChannels << endl;
	cout << "pixel depth:\t" << orig->depth << " bits" << endl;
	cout << "width:\t" << orig->width << " pixels" << endl;
	cout << "height:\t" << orig->height << " pixels" << endl;
	cout << "size:\t" << orig->imageSize << " bytes" << endl;
	cout << "width step:\t" << orig->widthStep << " bytes" << endl;
	cvWaitKey(0);
	cvReleaseImage(&orig);
	cvShowImage("copy",copy);
	cvWaitKey(0);
	cvReleaseImage(&copy);
	cvDestroyAllWindows();
}