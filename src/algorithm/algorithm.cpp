#include "algorithm.hpp" // Includes header file 


// Takes angular velaocity as a double and returns the comnputed steering wheel angle
double calculateSteeringWheelAngle(double angularVelocityZ) {
    // Scale the angular velocity to compute the steering angle
    // So if angularV is 100 then steeringAngle will be 0.3
    const double scalingFactor = 0.003; 
    double steeringAngle = angularVelocityZ * scalingFactor;

    // Apply limits to the steering angle to set a maximum steering range
    const double maxSteeringAngle = 0.21; //Corresponds to 12 degrees
    const double minSteeringAngle = -0.21; // Corresponds to -12 degrees


    // Checks if the steering angle is within the limits
    // If the steering angle exceeds the limits, it is set to the maximum or minimum value
    if (steeringAngle > maxSteeringAngle) {
        steeringAngle = maxSteeringAngle;
    } else if (steeringAngle < minSteeringAngle) {
        steeringAngle = minSteeringAngle;
    }

    return steeringAngle; // Returns the computed steering angle
}
