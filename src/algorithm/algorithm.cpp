// C++ file for algorithm

#include "algorithm.hpp"

double calculateSteeringWheelAngle(double angularVelocityZ) {
    // Scale the angular velocity to compute the steering angle
    const double scalingFactor = 0.003; // Adjust this factor as needed
    double steeringAngle = angularVelocityZ * scalingFactor;

    // Apply limits to the steering angle
    const double maxSteeringAngle = 0.21;
    const double minSteeringAngle = -0.21;

    if (steeringAngle > maxSteeringAngle) {
        steeringAngle = maxSteeringAngle;
    } else if (steeringAngle < minSteeringAngle) {
        steeringAngle = minSteeringAngle;
    }

    return steeringAngle;
}