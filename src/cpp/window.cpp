#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "window.hpp"
#include "objectDetection.hpp"

cv::VideoCapture cap(0);

cv::Mat BGRFrame;
cv::Mat HSVFrame;
cv::Mat mask;

cv::Scalar lowerColor = cv::Scalar(24, 10, 40);
cv::Scalar higherColor = cv::Scalar(44, 100, 160);

int lowH=21;
int lowS=100;
int lowV=100;
int highH=28;
int highS=255;
int highV=255;

objectDetection detection;

window::window(){
    if (!cap.isOpened()) {
        std::cerr << "error: could not open camera" << std::endl;
    }   

    cv::namedWindow("webcam feed", cv::WINDOW_NORMAL);

    cv::createTrackbar("lowH", "webcam feed", &lowH, 180, nullptr);
    cv::createTrackbar("lowS", "webcam feed", &lowS, 255, nullptr);
    cv::createTrackbar("lowV", "webcam feed", &lowV, 255, nullptr);
    cv::createTrackbar("highH", "webcam feed", &highH, 180, nullptr);
    cv::createTrackbar("highS", "webcam feed", &highS, 255, nullptr);
    cv::createTrackbar("highV", "webcam feed", &highV, 255, nullptr);

}

void window::refreshWindow(){
    cap >> BGRFrame;

    lowerColor = cv::Scalar(lowH, lowS, lowV);
    higherColor = cv::Scalar(highH, highS, highV);

    detection.detectColor(lowerColor, higherColor, BGRFrame, HSVFrame, mask, detection.contours);

    cv::imshow("webcam feed", mask);

    detection.canMoveCursor(detection.contours);
}
