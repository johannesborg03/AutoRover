#pragma once // Prevents redefintion or multiple defintion and is used instead of #define etc.
#include "../ConeDetector/ConeDetector.hpp"

double calculateSteeringWheelAngle(const ConePositions& cones, int imgWidth, double angularVelocityZ);