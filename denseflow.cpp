#include <vector>
#include <stdio.h>
#include <opencv2/opencv.hpp> // Requires: apt install libopencv-dev python3-opencv
#include "denseflow.h"
#define GRID_SIZE 20
#define AMPLIFICATION 1

void DenseFlow::initialize() {
	if(channel>=0) cap.open(channel);
	else cap.open(vidflow);
	cap >> prev;
	cvtColor(prev, prev, cv::COLOR_BGR2GRAY);
	fps=cap.get(cv::CAP_PROP_FPS);
	size=cv::Size((int)cap.get(cv::CAP_PROP_FRAME_WIDTH), (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT));
}
void DenseFlow::drawVectors() {
	for(int y=0; y<next.rows; y+=GRID_SIZE) {
		for(int x=0; x<next.cols; x+=GRID_SIZE) {
			const cv::Point2f flowatxy = flow.at<cv::Point2f>(y, x) * 1;
			line(colored, cv::Point(x, y), cv::Point(cvRound(x + flowatxy.x*AMPLIFICATION), cvRound(y + flowatxy.y*AMPLIFICATION)), cv::Scalar(0, 255, 0));
			circle(colored, cv::Point(x, y), 1, cv::Scalar(0, 0, 0), -1);
		}
	}
}
void DenseFlow::calculateFlow() {
	cap >> next;
	if(next.empty()) { cap.release(); active=false; } else {
		next.copyTo(colored);
		cvtColor(next, next, cv::COLOR_BGR2GRAY);
		cv::calcOpticalFlowFarneback(prev, next, flow, 0.4, 1, 12, 2, 8, 1.2, 0);
		if(draw) drawVectors();
		next.copyTo(prev);
	}
}
