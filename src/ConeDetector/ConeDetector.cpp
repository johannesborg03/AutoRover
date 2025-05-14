#include "ConeDetector.hpp"
#include <opencv2/imgproc/imgproc.hpp> 
#include <opencv2/core/core.hpp> 
#include <vector>

ConeDetector::ConeDetector(cv::Scalar lowerHSV, cv::Scalar upperHSV)
    : m_lowerHSV(lowerHSV), m_upperHSV(upperHSV) {}

std::vector<cv::Rect> ConeDetector::detectCones(const cv::Mat &frame) {
    cv::Mat hsvImage, mask;
    std::vector<cv::Rect> detectedCones;

    // Convert to HSV color space.
    cv::cvtColor(frame, hsvImage, cv::COLOR_BGR2HSV);

    // Threshold the HSV image to isolate the desired color range.
    cv::inRange(hsvImage, m_lowerHSV, m_upperHSV, mask);

    // Perform morphological operations to clean up the mask.
    cv::erode(mask, mask, cv::Mat(), cv::Point(-1, -1), 2);
    cv::dilate(mask, mask, cv::Mat(), cv::Point(-1, -1), 2);

    // Find contours of the detected cones.
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // Create bounding boxes for each detected cone.
    for (const auto &contour : contours) {
        detectedCones.push_back(cv::boundingRect(contour));
    }

    return detectedCones;
}