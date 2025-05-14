#ifndef CONEDETECTOR_HPP
#define CONEDETECTOR_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

class ConeDetector {
public:
    ConeDetector(cv::Scalar lowerHSV, cv::Scalar upperHSV);
    std::vector<cv::Rect> detectCones(const cv::Mat &frame);

private:
    cv::Scalar m_lowerHSV;
    cv::Scalar m_upperHSV;
};

#endif // CONEDETECTOR_HPP