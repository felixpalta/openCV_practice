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

//CvArr arr; // can't create just 'void' object



int main()
{
	using namespace std;
	// mat points to CvMat type structure . mat->data points to data itself
	// cvCreateMatHeader allocates space for CvMat type structure and returns pointer to it, mat->data points to NULL
	// cvCreateData allocates space for data, so mat->data could point to it.
	// cvRelaseData makes mat->data point to NULL. But mat still points to existing structure.
	// cvCreateMat creates allocates space for both structure and data, and returns pointer to structure. mat->data points to allocated space.
	// cvReleaseMat frees space, pointed to by mat->data and by mat itself. So now mat points to NULL.

	CvMat *mat = cvCreateMatHeader(3,5,CV_32SC1); // creates matrix structure with NULL data pointer
	cvCreateData(mat);	// allocates space for the matrix, data pointer points to that space, but doesn't free the structure pointer itself
	cvReleaseData(mat);	// data pointer is to NULL again

	mat = cvCreateMat(4,5,CV_8UC1);
	


	unsigned char *c = CV_MAT_ELEM_PTR_FAST(*mat,2,2,sizeof(unsigned char));
	*c = 'x';
	CV_MAT_ELEM(*mat,unsigned char,2,2) = '!'; // access using macro
	*cvPtr2D(mat,2,2,CV_8UC1) = '0'; // access using method
	*cvPtr1D(mat,16,CV_8UC1) = '?'; // can access element of 2d-array as 1d-array
	cout << *c << endl;

	cvSave("matrix.xml",mat,"wtf","wololo!");
	//CvMat *copy = cvCreateMat(4,5,CV_8UC1);

	CvMat *copy =	(CvMat *) cvLoad("matrix.xml");

	for(int i=0; i<copy->rows; i++){
		for(int j=0; j<copy->cols; j++){
			cout << CV_MAT_ELEM( *copy, unsigned char, i, j) << ' ';
			
		}
		cout << endl;
	}
	printf("-----\n");
	
	

	cvReleaseMat(&mat);
	cvReleaseMat(&copy);

	IplImage *img = cvLoadImage("cat.jpg");

	for( int y=0; y<img->height; y++ ) {
		for( int x=0; x<img->width; x++ ) {
			CvScalar pix = cvGet2D(img,y,x);
			
			
			cvSet2D(img,y,x,pix);
		}
	}
	cvShowImage("desu",img);


	cvReleaseImage(&img);
	


	cvWaitKey();
	

}