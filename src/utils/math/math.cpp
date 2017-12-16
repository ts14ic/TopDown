#include "math.h"
#include <cmath>
#include <cstdlib>

using namespace math;

double detail::cartesianCos(double x) {
    return std::cos(toRadians(x));
}

double detail::cartesianSin(double x) {
    return std::sin(toRadians(x));
}

double detail::radianCos(double x) {
    return std::cos(x);
}

double detail::radianSin(double x) {
    return std::sin(x);
}

double detail::getDistance(double ax, double ay, double bx, double by) {
    return std::hypot(bx - ax, by - ay);
}

double detail::getAngle(double ax, double ay, double bx, double by) {
    return std::atan2(by - ay, bx - ax);
}
