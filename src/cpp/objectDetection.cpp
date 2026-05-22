#include "objectDetection.hpp"
#include <opencv2/opencv.hpp>
#include "cursorMovment.hpp"
#include "objectDetection.hpp"
#include <iostream>
#include <cmath>

void objectDetection::detectColor(cv::Scalar low, cv::Scalar high, cv::Mat& bgr, cv::Mat& hsv, cv::Mat& mask, std::vector<std::vector<cv::Point>>& contours){
    maxArea = 0;
    largestContourIndex = -1; 
    contours.clear();

    cv::cvtColor(bgr, hsv, cv::COLOR_BGR2HSV);
    cv::inRange(hsv, low, high, mask);

    cv::Mat kernel = getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(mask, mask, cv::MORPH_OPEN, kernel);

    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for (size_t i = 0; i < contours.size(); i++) {
        if (cv::contourArea(contours[i]) < 2000) {
            continue;
        }

        cv::Rect bbox = cv::boundingRect(contours[i]);
        cv::rectangle(bgr, bbox, cv::Scalar(0, 255, 0), 2);
        // cv::putText(bgr, "object detected", bbox.tl(),
        // cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 255, 0), 1);
        
        double area = cv::contourArea(contours[i]);
        if (area > maxArea) {
            maxArea = area;
            largestContourIndex = i;
        }
    }

    findFingers(contours, largestContourIndex);
}

void objectDetection::canMoveCursor(std::vector<std::vector<cv::Point>>& contours) {
    if (largestContourIndex != -1 && maxArea > 500) {
        cv::Moments m = cv::moments(contours[largestContourIndex]);
        if (std::abs(m.m00) > 0) {
            int pX = m.m10 / m.m00;
            int pY = m.m01 / m.m00;

            if (prevX != -1 && prevY != -1) {
                float sensitivity = 3.0f;
                int deltaX = pX - prevX;
                int deltaY = pY - prevY;

                if(deltaX > 0){
                    deltaX = deltaX * -1;
                }else{
                    deltaX = std::abs(deltaX);
                }

                int deadZone = 2;
                if (std::abs(deltaX) < deadZone) deltaX = 0;
                if (std::abs(deltaY) < deadZone) deltaY = 0;
                if (deltaX == 0 && deltaY == 0) {
                    prevX = pX;
                    prevY = pY;
                    return;
                }

                float smoothing = 0.4f;

                smoothX = smoothX * smoothing + deltaX * (1.0f - smoothing);
                smoothY = smoothY * smoothing + deltaY * (1.0f - smoothing);

                cursor.moveCursor((int)(smoothX * sensitivity), (int)(smoothY * sensitivity));

            }
            prevX = pX;
            prevY = pY;
        }
    } else {
        prevX = -1;
        prevY = -1;
    }
}

double objectDetection::getAngle(cv::Point far, cv::Point start, cv::Point end) {
    double l1 = cv::norm(start - far);
    double l2 = cv::norm(end - far);
    double dot = (start - far).dot(end - far);
    return std::acos(dot / (l1 * l2)) * 180.0 / CV_PI;
}

void objectDetection::findFingers(const std::vector<std::vector<cv::Point>>& contours, int largestContour) {
    if (contours.empty() || largestContour < 0 || largestContour >= static_cast<int>(contours.size())) {
        std::cout << "Invalid contour index" << std::endl;
        return;
    }

    const std::vector<cv::Point>& handContour = contours[largestContour];
    
    if (handContour.size() < 3){return;} 

    std::vector<int> hullIndices;
    cv::convexHull(handContour, hullIndices, true, false); 

    int fingerCount = 0;
    
    if (hullIndices.size() > 3) {
        std::vector<cv::Vec4i> defects;
        
        try {
            cv::convexityDefects(handContour, hullIndices, defects);

            for (const auto& defect : defects) {
                if (defect[0] >= handContour.size() || 
                    defect[1] >= handContour.size() || 
                    defect[2] >= handContour.size())
                {continue;}

                cv::Point start = handContour[defect[0]];
                cv::Point end = handContour[defect[1]];
                cv::Point far = handContour[defect[2]];
                float depth = defect[3] / 256.0f;

                if (depth > 20.0f) {
                    double angle = getAngle(far, start, end);
                    if (angle < 90.0) {
                        fingerCount++;
                    }
                }
            }

            if (fingerCount > 0) {
                fingerCount += 1; 
            }
        } 
        catch (const cv::Exception& e) {
            std::cerr << "OpenCV Exception in convexityDefects: " << e.what() << std::endl;
        }
    }
    std::cout << "Fingers extended: " << fingerCount << std::endl;

    //true is left click and false is right click
    if(fingerCount == 2 && hasLeftClicked == false){
        cursor.click(true);
        hasLeftClicked = true;
    }else if(fingerCount == 0 && hasRightClicked == false){
        cursor.click(false);
        hasRightClicked = true;
    }else if(fingerCount == 3){
        hasLeftClicked = false;
        hasRightClicked = false;
    }
    
}