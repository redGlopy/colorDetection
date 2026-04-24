#include <opencv2/opencv.hpp>
#include <iostream>

int main() {

    // takes iformation from the spesified webcam
    cv::VideoCapture cap(0);

    // checks if the webcam is open
    if (!cap.isOpened()) {
        std::cerr << "error: could not open camera" << std::endl;
        return -1;
    }

    // a frame to display later
    cv::Mat frame;

    // creates a window to display the frame on
    cv::namedWindow("webcam feed");

    // the main loop that displays the frame
    while (cv::getWindowProperty("webcam feed", cv::WND_PROP_VISIBLE) >= 1) {

        //puts the information fromt he start into the frame
        cap >> frame;
        if (frame.empty()) break;

        // updates the window to display the frame
        cv::imshow("webcam feed", frame);

        // close the window and brake the loop if Esc is pressed
        if (cv::waitKey(10) == 27) break; 
    }

    return 0;
}
