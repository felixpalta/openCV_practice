#include <opencv2/opencv.hpp>

int main()
{
	cv::Mat img = cv::imread("cat.jpg");
	cv::imshow("img", img);
	cv::waitKey(0);
	return 0;
}