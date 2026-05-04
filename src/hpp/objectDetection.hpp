#pragma once

#include <opencv2/opencv.hpp>
#include "cursorMovment.hpp"

class objectDetection{
    public:
        std::vector<std::vector<cv::Point>> contours;
        void detectColor(cv::Scalar low, cv::Scalar high, cv::Mat bgr, cv::Mat hsv, cv::Mat mask, std::vector<std::vector<cv::Point>> contours);
        void canMoveCursor(std::vector<std::vector<cv::Point>> contours);
    private:
        cursorMovment cursorMovment;
};