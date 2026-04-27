#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <windows.h>

cv::VideoCapture cap(0);

cv::Mat BGRFrame;
cv::Mat HSVFrame;
cv::Mat mask;

cv::Scalar lowerYellow = cv::Scalar(25, 50, 50);
cv::Scalar higherYellow = cv::Scalar(35, 255, 255);

void mainLoop();
void moveCursor(int dx, int dy);
void toggleFullscreen();

int main() {

    // moveCursor(100 , 100);

    if (!cap.isOpened()) {
        std::cerr << "error: could not open camera" << std::endl;
        return -1;
    }

    cv::namedWindow("webcam feed", cv::WINDOW_NORMAL);

    mainLoop();

    return 0;
}

void mainLoop(){
    while (cv::getWindowProperty("webcam feed", cv::WND_PROP_VISIBLE) >= 1) {

        toggleFullscreen();

        cap >> BGRFrame;
        if (BGRFrame.empty()) {
            break;
        }

        cv::cvtColor(BGRFrame, HSVFrame, cv::COLOR_BGR2HSV);
        cv::inRange(HSVFrame, lowerYellow, higherYellow, mask);

        cv::Mat kernel = getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
        cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel);

        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        for (size_t i = 0; i < contours.size(); i++) {
            if (cv::contourArea(contours[i]) < 500) {
                continue;
            }

            cv::Rect bbox = cv::boundingRect(contours[i]);
            cv::rectangle(BGRFrame, bbox, cv::Scalar(0, 255, 0), 2);

            cv::putText(BGRFrame, "object detected", bbox.tl(), 
            cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 1);
        }        
        
        cv::imshow("webcam feed", BGRFrame);

        if (cv::waitKey(10) == 27) {
            break; 
        }
    }
}

void moveCursor(int x, int y) {
    int width = GetSystemMetrics(SM_CYSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    int absoluteX = (x * 65536) / width;
    int absoluteY = (y * 65536) / height;

    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dx = x;         
    input.mi.dy = y;         
    input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_MOVE; 
    
    SendInput(1, &input, sizeof(INPUT));
}

void toggleFullscreen(){
    static bool isFullscreen = false;

    int key = cv::waitKeyEx(1);

    if (key == 1122) { 
        if (isFullscreen) {
            cv::setWindowProperty("webcam feed", cv::WND_PROP_FULLSCREEN, cv::WINDOW_NORMAL);
            isFullscreen = false;
        }else {
            cv::setWindowProperty("webcam feed", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
            isFullscreen = true;
        }
    }
}
