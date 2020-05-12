/* See https://stackoverflow.com/questions/43482959/simple-dense-optical-flow-program-calcopticalflowfarneback-opencv-3-2-cpp */
#include <iostream>
#include <vector>
#include <stdio.h>
#include <opencv2/opencv.hpp> // Requires: apt install libopencv-dev python3-opencv
#define GRID_SIZE 20
#define GENERATE_OUTPUT false
using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
	cv::Mat flow, prev, next, nextOriginal, nextOriginalC;
	cv::VideoWriter writer;
	cv::VideoCapture cap;
	cap.open(std::string(argv[1])); // or cap.open(0);
	cv::namedWindow("OpticalFlow", cv::WINDOW_AUTOSIZE);
	cap >> prev;
	cvtColor(prev, prev, COLOR_BGR2GRAY);
	if(GENERATE_OUTPUT) writer.open("output.avi", CV_FOURCC('M', 'J', 'P', 'G'), cap.get(cv::CAP_PROP_FPS), cv::Size((int)cap.get(cv::CAP_PROP_FRAME_WIDTH), (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT)));
	while(cv::waitKey(1)!=113) {
		cap >> next;
		if(next.empty()) break;
		next.copyTo(nextOriginalC);
		cvtColor(next, next, COLOR_BGR2GRAY);
		next.copyTo(nextOriginal);
		cv::calcOpticalFlowFarneback(prev, next, flow, 0.4, 1, 12, 2, 8, 1.2, 0);
		//cv::calcOpticalFlowFarneback(prev, next, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
		for(int y=0; y<next.rows; y+=GRID_SIZE) {
			for(int x=0; x<next.cols; x+=GRID_SIZE) {
				// get the flow from y, x position * 3 for better visibility
				const Point2f flowatxy = flow.at<Point2f>(y, x) * 1;
				// draw line at flow direction, *2 for viewability
				line(nextOriginalC, Point(x, y), Point(cvRound(x + flowatxy.x*2), cvRound(y + flowatxy.y*2)), Scalar(255, 0, 0));
				// draw initial point
				circle(nextOriginalC, Point(x, y), 1, Scalar(0, 0, 0), -1);
			}
		}
		nextOriginal.copyTo(prev);
		imshow("OpticalFlow", nextOriginalC);
		if(GENERATE_OUTPUT) writer << nextOriginalC;
	}
	cap.release();
	return 0;
}
