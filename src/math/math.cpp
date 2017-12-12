#include "math.h"
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
