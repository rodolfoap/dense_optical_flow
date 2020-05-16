#include <vector>
#include <stdio.h>
#include <opencv2/opencv.hpp> // Requires: apt install libopencv-dev python3-opencv
#define GRID_SIZE 20
#define GENERATE_OUTPUT false
#define AMPLIFICATION 1

class ChangeDetector{
public:
	cv::Mat flow, prev, next, nextOriginal, nextOriginalC;
	void improve1(){
		cvtColor(prev, prev, cv::COLOR_BGR2GRAY);
	}
	void process(){
		if(next.empty()) exit(1);
		next.copyTo(nextOriginalC);
		cvtColor(next, next, cv::COLOR_BGR2GRAY);
		next.copyTo(nextOriginal);
		cv::calcOpticalFlowFarneback(prev, next, flow, 0.4, 1, 12, 2, 8, 1.2, 0);
		for(int y=0; y<next.rows; y+=GRID_SIZE) {
			for(int x=0; x<next.cols; x+=GRID_SIZE) {
				// get the flow from y, x position * 3 for better visibility
				const cv::Point2f flowatxy = flow.at<cv::Point2f>(y, x) * 1;
				// draw line at flow direction, *2 for viewability
				line(nextOriginalC, cv::Point(x, y), cv::Point(cvRound(x + flowatxy.x*AMPLIFICATION), cvRound(y + flowatxy.y*AMPLIFICATION)), cv::Scalar(0, 255, 0));
				// draw initial point
				circle(nextOriginalC, cv::Point(x, y), 1, cv::Scalar(0, 0, 0), -1);
			}
		}
		nextOriginal.copyTo(prev);
		imshow("OpticalFlow", nextOriginalC);
	}
};

int main(int argc, char* argv[]) {
	ChangeDetector cd;
	cv::VideoWriter writer;
	cv::VideoCapture cap;
	//cap.open(std::string(argv[1]));
	cap.open(0);
	cv::namedWindow("OpticalFlow", cv::WINDOW_AUTOSIZE);
	cap >> cd.prev;
	cd.improve1();
	//if(GENERATE_OUTPUT) writer.open("output.avi", CV_FOURCC('M', 'J', 'P', 'G'), cap.get(cv::CAP_PROP_FPS), cv::Size((int)cap.get(cv::CAP_PROP_FRAME_WIDTH), (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT)));
	while(cv::waitKey(1)!=113) {
		cap >> cd.next;
		cd.process();
		//if(GENERATE_OUTPUT) writer << nextOriginalC;
	}
	cap.release();
	return 0;
}
