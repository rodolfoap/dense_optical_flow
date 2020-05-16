#include <vector>
#include <stdio.h>
#include <opencv2/opencv.hpp> // Requires: apt install libopencv-dev python3-opencv
#include "denseflow.h"
#define GRID_SIZE 20
#define AMPLIFICATION 1

int main(int argc, char* argv[]) {
	// DenseFlow dflow(0);
	DenseFlow dflow(argv[1]);

	// Vectors drawing
	cv::namedWindow("OpticalFlow", cv::WINDOW_AUTOSIZE);
	dflow.setDraw(true);

	// Video generation
	// cv::VideoWriter writer;
	// writer.open("output.avi", CV_FOURCC('M', 'J', 'P', 'G'), dflow.getFPS(), dflow.getSize());

	while(cv::waitKey(1)!=113 && dflow.isActive()) {
		dflow.calculateFlow();

		// Vectors drawing
		imshow("OpticalFlow", dflow.getImage());

		// Video generation
		// writer<<dflow.getImage();
	}
	return 0;
}
