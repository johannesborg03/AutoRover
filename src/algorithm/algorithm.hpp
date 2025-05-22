#pragma once // Prevents redefintion or multiple defintion and is used instead of #define etc.
#include "../ConeDetector/ConeDetector.hpp"
#include <opencv2/opencv.hpp>

double calculateSteeringWheelAngle(double angularVelocityZ);