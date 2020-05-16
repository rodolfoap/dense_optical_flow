#include "denseflow.h"

void DenseFlow::initialize() {
	if(channel>=0) cap.open(channel);
	else cap.open(vidflow);
	cap >> prev;
	cvtColor(prev, prev, cv::COLOR_BGR2GRAY);
	fps=cap.get(cv::CAP_PROP_FPS);
	size=cv::Size((int)cap.get(cv::CAP_PROP_FRAME_WIDTH), (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT));
	swidth=prev.cols/GRID_SIZE;
	sheight=prev.rows/GRID_SIZE;
	state=cv::Mat_<cv::Point>(sheight, swidth, cv::Point(0, 0));
}
void DenseFlow::drawVectors() {
	for(int y=0; y<sheight; y+=1) {
		for(int x=0; x<swidth; x+=1) {
			const cv::Point2f flowatxy=state.at<cv::Point2f>(y, x);
			line(colored, cv::Point(x*GRID_SIZE, y*GRID_SIZE), cv::Point(cvRound(x*GRID_SIZE + flowatxy.x*AMPLIFICATION), cvRound(y*GRID_SIZE + flowatxy.y*AMPLIFICATION)), cv::Scalar(0, 255, 0));
			circle(colored, cv::Point(x*GRID_SIZE, y*GRID_SIZE), 1, cv::Scalar(0, 0, 0), -1);
		}
	}
}
void DenseFlow::calculateFlow() {
	cap >> next;
	if(next.empty()) { cap.release(); active=false; } else {
		next.copyTo(colored);
		cvtColor(next, next, cv::COLOR_BGR2GRAY);
		cv::calcOpticalFlowFarneback(prev, next, flow, 0.4, 1, GRID_SIZE, 2, 8, 1.2, 0);
		// Delta-interpolate this!
		for(int y=0; y<sheight; y+=1) for(int x=0; x<swidth; x+=1) state.at<cv::Point2f>(y, x)=flow.at<cv::Point2f>(y*GRID_SIZE, x*GRID_SIZE) * 1;
		if(draw) drawVectors();
		next.copyTo(prev);
	}
}
