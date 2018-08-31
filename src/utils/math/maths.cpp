#include "maths.h"
#include <cmath>

using namespace math;

const double math::PI = M_PI;
const double math::PI_OVER_180 = PI / 180.0;
const double math::PI_UNDER_180 = 180.0 / PI;

double detail::cartesianCos(double cartesianAngle) {
    return std::cos(toRadians(cartesianAngle));
}

double detail::cartesianSin(double cartesianAngle) {
    return std::sin(toRadians(cartesianAngle));
}

double detail::radianCos(double radianAngle) {
    return std::cos(radianAngle);
}

double detail::radianSin(double radianAngle) {
    return std::sin(radianAngle);
}

double detail::getDistance(double lhsX, double lhsY, double rhsX, double rhsY) {
    return std::hypot(rhsX - lhsX, rhsY - lhsY);
}

double detail::getAngle(double lhsX, double lhsY, double rhsX, double rhsY) {
    return std::atan2(rhsY - lhsY, rhsX - lhsX);
}
