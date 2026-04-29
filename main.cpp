#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <windows.h>

cv::VideoCapture cap(0);

cv::Mat BGRFrame;
cv::Mat HSVFrame;
cv::Mat mask;

cv::Scalar lowerYellow = cv::Scalar(20, 50, 50);
cv::Scalar higherYellow = cv::Scalar(25, 255, 255);

void mainLoop();
void moveCursor(int x, int y);

int main() {


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

        double maxArea = 0;
        int largestContourIndex = -1;

        for (size_t i = 0; i < contours.size(); i++) {
            if (cv::contourArea(contours[i]) < 1000) {
                continue;
            }

            cv::Rect bbox = cv::boundingRect(contours[i]);
            cv::rectangle(BGRFrame, bbox, cv::Scalar(0, 255, 0), 2);

            cv::putText(BGRFrame, "object detected", bbox.tl(), 
            cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 1);

            double area = cv::contourArea(contours[i]);
            if (area > maxArea) {
                maxArea = area;
                largestContourIndex = i;
            }
        }        
        
        cv::imshow("webcam feed", BGRFrame);

        if (largestContourIndex != -1) {
            if (maxArea > 1000) { 
                cv::Moments m = cv::moments(contours[largestContourIndex]);
                if (m.m00 > 0) {
                    int pX = m.m10 / m.m00;
                    int pY = m.m01 / m.m00;
                    pX = 600 - pX;
                    moveCursor((pX-300)/3, (pY-200)/3);
                }
            }
        }

        if (cv::waitKey(10) == 27) {
            break; 
        }
    }
}

void moveCursor(int x, int y) {
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    int absoluteX = (x / width) * 65536;
    int absoluteY = (y / height) * 65536;

    INPUT input = {0};
    input.type = INPUT_MOUSE;
    input.mi.dx = x;         
    input.mi.dy = y;         
    input.mi.dwFlags = MOUSEEVENTF_MOVE; 
    
    SendInput(1, &input, sizeof(INPUT));
}
