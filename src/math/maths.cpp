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

double detail::get_distance(double lhs_x, double lhs_y, double rhs_x, double rhs_y) {
    return std::hypot(rhs_x - lhs_x, rhs_y - lhs_y);
}

double detail::get_radian_angle(double lhs_x, double lhs_y, double rhs_x, double rhs_y) {
    return std::atan2(rhs_y - lhs_y, rhs_x - lhs_x);
}
