#include "calculations.h"
#include <cmath>
#include <cstdlib>

double detail::cartesianCos(double x) {
    return std::cos(toRadians(x));
}

double detail::cartesianSin(double x) {
    return std::sin(toRadians(x));
}

double detail::getDistance(double ax, double ay, double bx, double by) {
    return std::hypot(bx - ax, by - ay);
}

double detail::getAngle(double ax, double ay, double bx, double by) {
    return std::atan2(by - ay, bx - ax);
}

// todo replace with uniform_real_distribution
float rand_float(float range) {
    float k = (float) rand() / RAND_MAX;
    return range * (k * 2 - 1);
}
