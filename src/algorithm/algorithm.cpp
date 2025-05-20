// C++ file for algorithm

#include "algorithm.hpp"
#include <algorithm>
#include <cmath>

double calculateSteeringWheelAngle(const ConePositions& cones, int imgWidth, double angularVelocityZ) {
    // Only use cone-based calculation, ignore angularVelocityZ

    int centerX = imgWidth / 2;
    double steeringAngle = 0.0;

    if (!cones.yellowCones.empty() && !cones.blueCones.empty()) {
        int avgYellowX = 0, avgBlueX = 0;
        for (const auto& pt : cones.yellowCones) avgYellowX += pt.x;
        avgYellowX /= cones.yellowCones.size();
        for (const auto& pt : cones.blueCones) avgBlueX += pt.x;
        avgBlueX /= cones.blueCones.size();
        int trackCenter = (avgYellowX + avgBlueX) / 2;
        double error = centerX - trackCenter; // <-- flip sign here
        steeringAngle = error / static_cast<double>(centerX);
    }
    else if (!cones.yellowCones.empty()) {
        int avgYellowX = 0;
        for (const auto& pt : cones.yellowCones) avgYellowX += pt.x;
        avgYellowX /= cones.yellowCones.size();
        double error = centerX - avgYellowX; // <-- flip sign here
        steeringAngle = error / static_cast<double>(centerX);
    }
    else if (!cones.blueCones.empty()) {
        int avgBlueX = 0;
        for (const auto& pt : cones.blueCones) avgBlueX += pt.x;
        avgBlueX /= cones.blueCones.size();
        double error = centerX - avgBlueX; // <-- flip sign here
        steeringAngle = error / static_cast<double>(centerX);
    }

    steeringAngle = std::clamp(steeringAngle, -1.0, 1.0);
    return steeringAngle;
}