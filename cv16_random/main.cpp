#include <cv.h>
#include <highgui.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

const char *inWinName = "original";
const char *outWinName = "result";
const char *defaultName = "cat.jpg";
const char ESC = 27;
const char ENTER = 13;

int main()
{
	using namespace std;

	char *filename = "cat.jpg";
	IplImage *src = cvLoadImage(filename);
	IplImage *dst = cvCloneImage(src);
	cvNamedWindow(inWinName,CV_WINDOW_AUTOSIZE);
	cvNamedWindow(outWinName,CV_WINDOW_AUTOSIZE);

	CvRNG rng = cvRNG(0xffffffff); // default seed = -1
	int noisecount = 0;

	for (int i = 0; i < dst->height; ++i)
		for (int j = 0; j < dst->width; ++j){
			if (cvRandInt(&rng)%100 >= 90){
				CvScalar s = cvGet2D(dst,i,j);
				for (int k = 0; k < 4; ++k)
				{
					s.val[k] = cvRandInt(&rng)%255;
				}
				cvSet2D(dst,i,j,s);
				++noisecount;
			}
		}
	cout << "noisecount: " << noisecount << ", that is: " << 100 * noisecount/(dst->height*dst->width) << " %" << endl;
	cvShowImage(inWinName,src);
	cvShowImage(outWinName,dst);
	cvWaitKey();
	cvReleaseImage(&src); cvReleaseImage(&dst);
	cvDestroyAllWindows();

}