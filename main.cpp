#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    std::cout << "Starting OpenCV app..." << std::endl;
    // Create a 400x400 blue image (BGR format)
    cv::Mat image(400, 400, CV_8UC3, cv::Scalar(255, 0, 0));

    // Check if image was created
    if(image.empty()) {
        std::cout << "Could not create the image!" << std::endl;
        return -1;
    }

    // Add some text
    cv::putText(image, "OpenCV is Working!", 
                cv::Point(50, 200), 
                cv::FONT_HERSHEY_SIMPLEX, 1.0, 
                cv::Scalar(255, 255, 255), 2);

    // Show the image in a window
    cv::imshow("Validation Window", image);

    std::cout << "Press any key to close the window..." << std::endl;
    cv::waitKey(0); // Wait for a key press to close
    return 0;
}
