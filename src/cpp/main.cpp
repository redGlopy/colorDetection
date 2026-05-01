#include "window.hpp"
#include <opencv2/opencv.hpp>

int main() {
    window window;

    while (cv::getWindowProperty("webcam feed", cv::WND_PROP_VISIBLE) >= 1) {
        window.refreshWindow();
        if (cv::waitKey(10) == 27){
            break;
        }
    }
    return 0;
}
