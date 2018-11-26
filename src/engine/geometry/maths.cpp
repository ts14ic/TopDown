#include "maths.h"
#include <cmath>

using namespace math;

const double math::PI = M_PI;
const double math::PI_OVER_180 = PI / 180.0;
const double math::PI_UNDER_180 = 180.0 / PI;

double detail::cartesian_cos(double cartesian_angle) {
    return std::cos(to_radians(cartesian_angle));
}

double detail::cartesian_sin(double cartesian_angle) {
    return std::sin(to_radians(cartesian_angle));
}

double detail::radian_cos(double radian_angle) {
    return std::cos(radian_angle);
}

double detail::radian_sin(double radian_angle) {
    return std::sin(radian_angle);
}

double detail::get_distance(Point2d<double> lhs, Point2d<double> rhs) {
    return std::hypot(rhs.x - lhs.x, rhs.y - lhs.y);
}

double detail::get_radian_angle(Point2d<double> lhs, Point2d<double> rhs) {
    return std::atan2(rhs.y - lhs.y, rhs.x - lhs.x);
}
