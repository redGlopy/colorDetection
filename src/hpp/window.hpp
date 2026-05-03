#pragma once
#include "cursorMovment.hpp"
#include <opencv2/opencv.hpp>

class window{
    public:
        window();
        void refreshWindow();

    private: 
        cursorMovment cursorMovment;
        // cv::Mat BGRFrame;
        // cv::Mat HSVFrame;
        // cv::Mat mask;
};