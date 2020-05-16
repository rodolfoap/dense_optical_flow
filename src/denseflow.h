#include <opencv2/opencv.hpp> // Requires: apt install libopencv-dev python3-opencv
#define GRID_SIZE 20
#define AMPLIFICATION 20
#define ACCELERATION 0.2f
#define THRESHOLD 0.2f

class DenseFlow {
private:
	bool active=true, draw=false;
	cv::Mat state, flow, prev, next, colored;
	cv::VideoCapture cap;
	int channel;
	std::string vidflow;
	float fps;
	cv::Size size;
	int swidth, sheight;
	void initialize();

public:
	// Alternative constructors, allowing video files, streams or the local webcam
	DenseFlow(int c):   channel(c) { initialize(); }
	DenseFlow(char* f): channel(-1), vidflow(f) { initialize(); }

	// Not always, vectors are drawn over the original image
	void drawVectors();

	// Main calculating function
	void calculateFlow();

	// Getters & setters
	float getFPS()      { return fps; }
	bool isActive()     { return active; }
	cv::Size getSize()  { return size; }
	cv::Mat& getImage() { return colored; }
	cv::Mat& getFlow()  { return flow; }
	cv::VideoCapture& getVideoCapture() { return cap; }
	void setDraw(bool state) { draw=state; }
};
