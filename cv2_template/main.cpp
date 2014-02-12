//#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

//#include <videoInput.h>

std::string inWinName = "original";
const std::string outWinName = "result";

const std::string  defaultName = "cat.jpg";

const char ESC = 27;
const char ENTER = 13;

int main(int argc, char *argv[])
{
	using namespace std;
	using namespace cv;

	const string filename = (argc > 1) ? argv[1] : defaultName;
	
	Mat src = imread(filename,IMREAD_UNCHANGED);
	if (src.empty()){
		cout << "Can't load image: " << filename << endl;
		cin.ignore();
		exit(1);
	}
	cout << "Image loaded: " << filename << endl;
	
	inWinName += ": " + filename;

	imshow(inWinName,src);

	waitKey();
	
	destroyAllWindows();
}