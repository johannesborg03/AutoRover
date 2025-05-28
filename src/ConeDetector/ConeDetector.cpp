#include "ConeDetector.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

// HSV thresholds for blue and yellow cones
const cv::Scalar BLUE_MIN(100, 60, 40);
const cv::Scalar BLUE_MAX(135, 255, 135);
const cv::Scalar YELLOW_MIN(10, 0, 140);
const cv::Scalar YELLOW_MAX(75, 255, 255);

// This function takes an image as input and returns the detected cone positions for 
// both blue and yellow cones
ConePositions detectCones(const cv::Mat& img) {
    ConePositions cones;

    // Region of Interest which is the area where cones are expected to be found
    cv::Rect roi(60, 250, 480, 140);
    cv::Mat roiImg = img(roi).clone();

    // Convert to the image from the OpenCV color format to HSV
    cv::Mat hsv;
    cv::cvtColor(roiImg, hsv, cv::COLOR_BGR2HSV);

    // Creates two different masks which is used to filter out the colors of the cones
    // to detect the blue and yellow cones
    // The masks are created by applying the inRange function to the HSV image
    cv::Mat blueMask, yellowMask;
    cv::inRange(hsv, BLUE_MIN, BLUE_MAX, blueMask);
    cv::inRange(hsv, YELLOW_MIN, YELLOW_MAX, yellowMask);

    // Morphology to clean up the masks so that the blobs represents cones and not noise.
    // The MORPH_OPEN removes the small noise and the
    // MORPH_CLOSE fills in small holes in the detected areas.
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5,5));
    cv::morphologyEx(blueMask, blueMask, cv::MORPH_OPEN, kernel);
    cv::morphologyEx(blueMask, blueMask, cv::MORPH_CLOSE, kernel);
    cv::morphologyEx(yellowMask, yellowMask, cv::MORPH_OPEN, kernel);
    cv::morphologyEx(yellowMask, yellowMask, cv::MORPH_CLOSE, kernel);

    // Find all the blue contours in the masks to detect the cones the same way as the yellow cones
    // described below
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
    std::vector<std::vector<cv::Point>> yellowContours; // yellowCountours holds all the shapes from the yellow mask
    // Scans the mask for white shapes and stores each shape as a vector of point by calling the findContours function
    cv::findContours(yellowMask, yellowContours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE); 
    // Here we start a loop over every found countour in the yellowContours vector
    // To check which counters actually look like the cones we want to detect
    for (const auto& contour : yellowContours) {
        cv::Rect bbox = cv::boundingRect(contour); // USed for size and aspect ratio
        double area = cv::contourArea(contour); // Computes the area of the contour
        // If the counter is smaller than 15 pixels in width or height it is ignored
        if (bbox.width < 15 || bbox.height < 15) continue; 
        if (area < 20) continue; // if the area is smaller than 20 pixels it is ignored
        // Calculates the ratio of width to height so that
        // if the countour is too wide or too narrow it is ignored
        float aspect = float(bbox.width) / bbox.height;
        if (aspect < 0.2 || aspect > 2.0) continue;
        // Calculate the moments of the contour to find the center of the cone
        // The moments are used to find the center of the contour
        auto m = cv::moments(contour);
        if (m.m00 == 0) continue; // If the zeroth moment is zero, the contour is ignored to avoid division by zero
        int coneX = int(m.m10/m.m00) + roi.x; // The x coordinate of the cone is calculated by dividing the first moment by the zeroth moment
        int coneY = int(m.m01/m.m00) + roi.y; // The y is calculated the same way
        cones.yellowCones.emplace_back(coneX, coneY); // Stores the cone position in the yellowCones vector
    }

    // Sort by Y so that the closest cones are at the top
    auto sortByY = [](const cv::Point& a, const cv::Point& b) {
        return a.y > b.y;
    };
    std::sort(cones.blueCones.begin(), cones.blueCones.end(), sortByY);
    std::sort(cones.yellowCones.begin(), cones.yellowCones.end(), sortByY);

    // Limit to top 5 closest cones so that we dont flood the
    // logic to keep it simple and fast
    if (cones.blueCones.size() > 5) cones.blueCones.resize(5);
    if (cones.yellowCones.size() > 5) cones.yellowCones.resize(5);

    return cones; // Returns the position of 5 blue and 5 yellow cones sorted by distance
}
