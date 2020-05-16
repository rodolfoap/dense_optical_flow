#include <vector>
#include <stdio.h>
#include <opencv2/opencv.hpp> // Requires: apt install libopencv-dev python3-opencv
#define GRID_SIZE 20
#define AMPLIFICATION 1

class ChangeDetector{
private:
	cv::Mat flow, prev, next, nextOriginal, colored;
	cv::VideoCapture cap;
	int channel=-1;
	std::string vidflow;
	bool active=true;
	float fps;
	cv::Size size;
	void initialize(){
		if(channel>=0) cap.open(channel); else cap.open(vidflow);
		cv::namedWindow("OpticalFlow", cv::WINDOW_AUTOSIZE);
		cap >> prev;
		cvtColor(prev, prev, cv::COLOR_BGR2GRAY);
		fps=cap.get(cv::CAP_PROP_FPS);
		size=cv::Size((int)cap.get(cv::CAP_PROP_FRAME_WIDTH), (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT));
	}
public:
	ChangeDetector(std::string f): vidflow(f) { initialize(); }
	ChangeDetector(int c): channel(c)         { initialize(); }
	void processnext(){
		cap >> next;
		if(next.empty()) { cap.release(); active=false; } else {
			next.copyTo(colored);
			cvtColor(next, next, cv::COLOR_BGR2GRAY);
			next.copyTo(nextOriginal);
			cv::calcOpticalFlowFarneback(prev, next, flow, 0.4, 1, 12, 2, 8, 1.2, 0);
			for(int y=0; y<next.rows; y+=GRID_SIZE) {
				for(int x=0; x<next.cols; x+=GRID_SIZE) {
					const cv::Point2f flowatxy = flow.at<cv::Point2f>(y, x) * 1;
					line(colored, cv::Point(x, y), cv::Point(cvRound(x + flowatxy.x*AMPLIFICATION), cvRound(y + flowatxy.y*AMPLIFICATION)), cv::Scalar(0, 255, 0));
					circle(colored, cv::Point(x, y), 1, cv::Scalar(0, 0, 0), -1);
				}
			}
			nextOriginal.copyTo(prev);
			imshow("OpticalFlow", colored);
		}
	}
	float getFPS()      { return fps; }
	bool isActive()     { return active; }
	cv::Size getSize()  { return size; }
	cv::Mat  getImage() { return colored; }
};

int main(int argc, char* argv[]) {
	cv::VideoWriter writer;
	ChangeDetector cd(0); // cd(std::string(argv[1]));

	// Video generation: uncomment writers
	// writer.open("output.avi", CV_FOURCC('M', 'J', 'P', 'G'), cd.getFPS(), cd.getSize());

	while(cv::waitKey(1)!=113 && cd.isActive()) {
		cd.processnext();
		// writer<<cd.getImage();
	}
	return 0;
}
