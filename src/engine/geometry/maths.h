#pragma once

#include "Point2d.h"

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

        double get_distance(Point2d<double> lhs, Point2d<double> rhs);

        double get_radian_angle(Point2d<double> lhs, Point2d<double> rhs);
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
     * @param lhs First point
     * @param rhs Second point
     * @return Distance between two points
     */
    template <class R = float, class A, class B>
    R get_distance(Point2d<A> lhs, Point2d<B> rhs) {
        return static_cast<R>(detail::get_distance(
                point_cast<double>(lhs),
                point_cast<double>(rhs)
        ));
    }

    /**
     * Calculate radian angle between two points
     * @tparam R Output value type
     * @tparam A Input value type for first point
     * @tparam B Input value type for second point
     * @param lhs First point
     * @param rhs Second point
     * @return Radian angle between two points
     */
    template <class R = float, class A, class B>
    R get_radian_angle(Point2d<A> lhs, Point2d<B> rhs) {
        return static_cast<R>(detail::get_radian_angle(
                point_cast<double>(lhs),
                point_cast<double>(rhs)
        ));
    }

    /**
     * Calculate cartesian angle between two points
     * @tparam R Output value type
     * @tparam A Input value type for first point
     * @tparam B Input value type for second point
     * @param lhs First point
     * @param rhs Second point
     * @return Cartesian angle between two points
     */
    template <class R = float, class A, class B>
    R get_cartesian_angle(Point2d<A> lhs, Point2d<B> rhs) {
        return to_cartesian(get_radian_angle(lhs, rhs));
    }
}
