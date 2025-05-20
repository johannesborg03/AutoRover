#include "ConeDetector.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

// HSV thresholds for blue and yellow cones
const cv::Scalar BLUE_MIN(100, 50, 30);
const cv::Scalar BLUE_MAX(140, 255, 180);
const cv::Scalar YELLOW_MIN(15, 40, 120);
const cv::Scalar YELLOW_MAX(40, 255, 255);

ConePositions detectCones(const cv::Mat& img) {
    ConePositions cones;

    // Define ROI (adjust these values for your video)
    cv::Rect roi(60, 250, 485, 140);
    cv::Mat roiImg = img(roi).clone();

    cv::Mat hsv;
    cv::cvtColor(roiImg, hsv, cv::COLOR_BGR2HSV);

    // Yellow mask
    cv::Mat yellowMask;
    cv::inRange(hsv, YELLOW_MIN, YELLOW_MAX, yellowMask);

    // Blue mask
    cv::Mat blueMask;
    cv::inRange(hsv, BLUE_MIN, BLUE_MAX, blueMask);

    // Find contours for yellow cones
    std::vector<std::vector<cv::Point>> yellowContours;
    cv::findContours(yellowMask, yellowContours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    for (const auto& contour : yellowContours) {
        cv::Rect bbox = cv::boundingRect(contour);
        // Filter out small boxes (noise)
        if (bbox.width < 10 || bbox.height < 10) continue;
        cv::Moments m = cv::moments(contour);
        if (m.m00 != 0) {
            // Offset by ROI position to get coordinates in original image
            cones.yellowCones.push_back(cv::Point(static_cast<int>(m.m10 / m.m00) + roi.x,
                                                  static_cast<int>(m.m01 / m.m00) + roi.y));
        }
    }

    // Find contours for blue cones
    std::vector<std::vector<cv::Point>> blueContours;
    cv::findContours(blueMask, blueContours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    for (const auto& contour : blueContours) {
        cv::Rect bbox = cv::boundingRect(contour);
        if (bbox.width < 10 || bbox.height < 10) continue;
        cv::Moments m = cv::moments(contour);
        if (m.m00 != 0) {
            cones.blueCones.push_back(cv::Point(static_cast<int>(m.m10 / m.m00) + roi.x,
                                                static_cast<int>(m.m01 / m.m00) + roi.y));
        }
    } else {
        steeringAngle = 0.0; // or keep previous value
    }

    return cones;
}
