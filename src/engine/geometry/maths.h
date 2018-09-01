#pragma once

namespace math {
    // trigonometry
    extern const double PI;
    extern const double PI_OVER_180;
    extern const double PI_UNDER_180;

    namespace detail {
        double cartesian_cos(double cartesian_angle);

        double cartesian_sin(double cartesian_angle);

        double radian_cos(double radian_angle);

        double radian_sin(double radian_angle);

        double get_radian_angle(double lhs_x, double lhs_y, double rhs_x, double rhs_y);

        double get_distance(double lhs_x, double lhs_y, double rhs_x, double rhs_y);
    }

    /**
     * Transform a cartesian angle into a radian angle
     * @tparam R Radian angle value type
     * @tparam T Cartesian angle value type
     * @param cartesian_angle Cartesian angle
     * @return Angle in radian
     */
    template <class R = float, class T>
    R to_radians(T cartesian_angle) {
        return static_cast<R>(cartesian_angle * PI_OVER_180);
    }

    /**
     * Transform a radian angle into a cartesian angle
     * @tparam R Cartesian angle value type
     * @tparam T Radian angle value type
     * @param radian_angle Radian angle
     * @return Angle in cartesian
     */
    template <class R = float, class T>
    R to_cartesian(T radian_angle) {
        return static_cast<R>(radian_angle * PI_UNDER_180);
    }

    /**
     * Calculate the cosine value from a cartesian angle
     * @tparam R Input value type
     * @tparam T Output value type
     * @param cartesian_angle Cartesian angle
     * @return Cosine value
     */
    template <class R = float, class T>
    R cartesian_cos(T cartesian_angle) {
        return static_cast<R>(detail::cartesian_cos(cartesian_angle));
    }

    /**
     * Calculate the cosine value from a radian angle
     * @tparam R Input value type
     * @tparam T Output value type
     * @param radian_angle Radian angle
     * @return Cosine value
     */
    template <typename R = float, typename T>
    R radian_cos(T radian_angle) {
        return static_cast<R>(detail::radian_cos(radian_angle));
    }

    /**
     * Calculate the sine value from a radian angle
     * @tparam R Input value type
     * @tparam T Output value type
     * @param radian_angle Radian angle
     * @return Sine value
     */
    template <typename R = float, typename T>
    R radian_sin(T radian_angle) {
        return static_cast<R>(detail::radian_sin(radian_angle));
    }

    /**
     * Calculate the sine value from a cartesian angle
     * @tparam R Input value type
     * @tparam T Output value type
     * @param cartesian_angle Cartesian angle
     * @return Sine value
     */
    template <class R = float, class T>
    R cartesian_sin(T cartesian_angle) {
        return static_cast<R>(detail::cartesian_sin(cartesian_angle));
    }

    /**
     * Calculate distance between two points
     * @tparam R Output value type
     * @tparam A Input value type for first point
     * @tparam B Input value type for second point
     * @param lhs_x First point x coordinate
     * @param lhs_y First point y coordinate
     * @param rhs_x Second point x coordinate
     * @param rhs_y Second point y coordinate
     * @return Distance between two points
     */
    template <class R = float, class A, class B>
    R get_distance(A lhs_x, A lhs_y, B rhs_x, B rhs_y) {
        return static_cast<R>(detail::get_distance(lhs_x, lhs_y, rhs_x, rhs_y));
    }

    /**
     * Calculate radian angle between two points
     * @tparam R Output value type
     * @tparam A Input value type for first point
     * @tparam B Input value type for second point
     * @param lhs_x First point x coordinate
     * @param lhs_y First point y coordinate
     * @param rhs_x Second point x coordinate
     * @param rhs_y Second point y coordinate
     * @return Radian angle between two points
     */
    template <class R = float, class A, class B>
    R get_radian_angle(A lhs_x, A lhs_y, B rhs_x, B rhs_y) {
        return static_cast<R>(detail::get_radian_angle(lhs_x, lhs_y, rhs_x, rhs_y));
    }

    /**
     * Calculate cartesian angle between two points
     * @tparam R Output value type
     * @tparam A Input value type for first point
     * @tparam B Input value type for second point
     * @param lhs_x First point x coordinate
     * @param lhs_y First point y coordinate
     * @param rhs_x Second point x coordinate
     * @param rhs_y Second point y coordinate
     * @return Cartesian angle between two points
     */
    template <class R = float, class A, class B>
    R get_cartesian_angle(A lhs_x, A lhs_y, B rhs_x, B rhs_y) {
        return to_cartesian(get_radian_angle(lhs_x, lhs_y, rhs_x, rhs_y));
    }
}
