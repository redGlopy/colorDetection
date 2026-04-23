#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cerr << "error: could not open camera" << std::endl;
        return -1;
    }

    cv::Mat frame;

    std::string windowName = "webcam feed";
    cv::namedWindow(windowName);

    while (cv::getWindowProperty(windowName, cv::WND_PROP_VISIBLE) >= 1) {
        cap >> frame;
        if (frame.empty()) break;

        cv::imshow(windowName, frame);

        if (cv::waitKey(1) == 27) break; 
    }

    return 0;
}
