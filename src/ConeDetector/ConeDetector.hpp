#pragma once // Prevents redefintion or multiple defintion and is used instead of #define etc.
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

// Structure to hold cone positions
struct ConePositions {
    std::vector<cv::Point> yellowCones;
    std::vector<cv::Point> blueCones;
};

// Function declaration for cone detection
ConePositions detectCones(const cv::Mat& img);

