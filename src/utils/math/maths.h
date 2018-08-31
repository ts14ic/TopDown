#pragma once

namespace math {
    // trigonometry
    extern const double PI;
    extern const double PI_OVER_180;
    extern const double PI_UNDER_180;

    namespace detail {
        double cartesianCos(double cartesianAngle);

        double cartesianSin(double cartesianAngle);

        double radianCos(double radianAngle);

        double radianSin(double radianAngle);

        double getAngle(double lhsX, double lhsY, double rhsX, double rhsY);

        double getDistance(double lhsX, double lhsY, double rhsX, double rhsY);
    }

    /**
     * Transform a cartesian angle into a radian angle
     * @tparam R Radian angle value type
     * @tparam T Cartesian angle value type
     * @param cartesianAngle Cartesian angle
     * @return Angle in radian
     */
    template <class R = float, class T>
    R toRadians(T cartesianAngle) {
        return static_cast<R>(cartesianAngle * PI_OVER_180);
    }

    /**
     * Transform a radian angle into a cartesian angle
     * @tparam R Cartesian angle value type
     * @tparam T Radian angle value type
     * @param radianAngle Radian angle
     * @return Angle in cartesian
     */
    template <class R = float, class T>
    R toCartesian(T radianAngle) {
        return static_cast<R>(radianAngle * PI_UNDER_180);
    }

    /**
     * Calculate the cosine value from a cartesian angle
     * @tparam R Input value type
     * @tparam T Output value type
     * @param cartesianAngle Cartesian angle
     * @return Cosine value
     */
    template <class R = float, class T>
    R cartesianCos(T cartesianAngle) {
        return static_cast<R>(detail::cartesianCos(cartesianAngle));
    }

    /**
     * Calculate the cosine value from a radian angle
     * @tparam R Input value type
     * @tparam T Output value type
     * @param radianAngle Radian angle
     * @return Cosine value
     */
    template <typename R = float, typename T>
    R radianCos(T radianAngle) {
        return static_cast<R>(detail::radianCos(radianAngle));
    }

    /**
     * Calculate the sine value from a radian angle
     * @tparam R Input value type
     * @tparam T Output value type
     * @param radianAngle Radian angle
     * @return Sine value
     */
    template <typename R = float, typename T>
    R radianSin(T radianAngle) {
        return static_cast<R>(detail::radianSin(radianAngle));
    }

    /**
     * Calculate the sine value from a cartesian angle
     * @tparam R Input value type
     * @tparam T Output value type
     * @param cartesianAngle Cartesian angle
     * @return Sine value
     */
    template <class R = float, class T>
    R cartesianSin(T cartesianAngle) {
        return static_cast<R>(detail::cartesianSin(cartesianAngle));
    }

    /**
     * Calculate distance between two points
     * @tparam R Output value type
     * @tparam A Input value type for first point
     * @tparam B Input value type for second point
     * @param lhsX First point x coordinate
     * @param lhsY First point y coordinate
     * @param rhsX Second point x coordinate
     * @param rhsY Second point y coordinate
     * @return Distance between two points
     */
    template <class R = float, class A, class B>
    R getDistance(A lhsX, A lhsY, B rhsX, B rhsY) {
        return static_cast<R>(detail::getDistance(lhsX, lhsY, rhsX, rhsY));
    }

    /**
     * Calculate radian angle between two points
     * @tparam R Output value type
     * @tparam A Input value type for first point
     * @tparam B Input value type for second point
     * @param lhsX First point x coordinate
     * @param lhsY First point y coordinate
     * @param rhsX Second point x coordinate
     * @param rhsY Second point y coordinate
     * @return Radian angle between two points
     */
    template <class R = float, class A, class B>
    R getRadianAngle(A lhsX, A lhsY, B rhsX, B rhsY) {
        return static_cast<R>(detail::getAngle(lhsX, lhsY, rhsX, rhsY));
    }

    /**
     * Calculate cartesian angle between two points
     * @tparam R Output value type
     * @tparam A Input value type for first point
     * @tparam B Input value type for second point
     * @param lhsX First point x coordinate
     * @param lhsY First point y coordinate
     * @param rhsX Second point x coordinate
     * @param rhsY Second point y coordinate
     * @return Cartesian angle between two points
     */
    template <class R = float, class A, class B>
    R getCartesianAngle(A lhsX, A lhsY, B rhsX, B rhsY) {
        return toCartesian(getRadianAngle(lhsX, lhsY, rhsX, rhsY));
    }
}
