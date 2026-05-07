#pragma once

#include <opencv2/opencv.hpp>
#include "cursorMovment.hpp"

class objectDetection{
    public:
        std::vector<std::vector<cv::Point>> contours;
        void detectColor(cv::Scalar low, cv::Scalar high, cv::Mat& bgr, cv::Mat& hsv, cv::Mat& mask, std::vector<std::vector<cv::Point>>& contours);
        void canMoveCursor(std::vector<std::vector<cv::Point>>& contours);
    private:
        cursorMovment cursor;
        double maxArea = 0;
        int largestContourIndex = -1;
        int prevX = -1;
        int prevY = -1;
        float smoothX = 0;
        float smoothY = 0;
        void findFingers(cv::Mat frame, std::vector<std::vector<cv::Point>> contours, int largestConture);
};