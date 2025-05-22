#include "ConeDetector.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

// HSV thresholds for blue and yellow cones
const cv::Scalar BLUE_MIN(100, 60, 40);
const cv::Scalar BLUE_MAX(135, 255, 135);
const cv::Scalar YELLOW_MIN(10, 0, 140);
const cv::Scalar YELLOW_MAX(75, 255, 255);

ConePositions detectCones(const cv::Mat& img) {
    ConePositions cones;

    // Region of Interest (tweak as needed)
    cv::Rect roi(60, 250, 480, 140);
    cv::Mat roiImg = img(roi).clone();

    // Convert to HSV
    cv::Mat hsv;
    cv::cvtColor(roiImg, hsv, cv::COLOR_BGR2HSV);

    // Threshold to get blue and yellow masks
    cv::Mat blueMask, yellowMask;
    cv::inRange(hsv, BLUE_MIN, BLUE_MAX, blueMask);
    cv::inRange(hsv, YELLOW_MIN, YELLOW_MAX, yellowMask);

    // Morphology to clean up masks
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5,5));
    cv::morphologyEx(blueMask, blueMask, cv::MORPH_OPEN, kernel);
    cv::morphologyEx(blueMask, blueMask, cv::MORPH_CLOSE, kernel);
    cv::morphologyEx(yellowMask, yellowMask, cv::MORPH_OPEN, kernel);
    cv::morphologyEx(yellowMask, yellowMask, cv::MORPH_CLOSE, kernel);

    // Blue cones
    std::vector<std::vector<cv::Point>> blueContours;
    cv::findContours(blueMask, blueContours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    for (const auto& contour : blueContours) {
        cv::Rect bbox = cv::boundingRect(contour);
        double area = cv::contourArea(contour);
        if (bbox.width < 15 || bbox.height < 15) continue;
        if (area < 20) continue;
        float aspect = float(bbox.width) / bbox.height;
        if (aspect < 0.2 || aspect > 2.0) continue;        
        auto m = cv::moments(contour);
        if (m.m00 == 0) continue;
        int coneX = int(m.m10/m.m00) + roi.x;
        int coneY = int(m.m01/m.m00) + roi.y;
        cones.blueCones.emplace_back(coneX, coneY);
    }

    // Yellow cones 
    std::vector<std::vector<cv::Point>> yellowContours;
    cv::findContours(yellowMask, yellowContours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    for (const auto& contour : yellowContours) {
        cv::Rect bbox = cv::boundingRect(contour);
        double area = cv::contourArea(contour);
        if (bbox.width < 15 || bbox.height < 15) continue;
        if (area < 20) continue;
        float aspect = float(bbox.width) / bbox.height;
        if (aspect < 0.2 || aspect > 2.0) continue;
        auto m = cv::moments(contour);
        if (m.m00 == 0) continue;
        int coneX = int(m.m10/m.m00) + roi.x;
        int coneY = int(m.m01/m.m00) + roi.y;
        cones.yellowCones.emplace_back(coneX, coneY); 
    }

    // Sort by Y (lowest first)
    auto sortByY = [](const cv::Point& a, const cv::Point& b) {
        return a.y > b.y;
    };
    std::sort(cones.blueCones.begin(), cones.blueCones.end(), sortByY);
    std::sort(cones.yellowCones.begin(), cones.yellowCones.end(), sortByY);

    // Limit to top 5 closest cones
    if (cones.blueCones.size() > 5) cones.blueCones.resize(5);
    if (cones.yellowCones.size() > 5) cones.yellowCones.resize(5);

    return cones;
}
