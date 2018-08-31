#pragma once

namespace math {
    // trigonometry
    constexpr float PI = 3.14159265359f;
    constexpr float PI_OVER_180 = PI / 180.f;
    constexpr float PI_UNDER_180 = 180.f / PI;

    namespace detail {
        double cartesianCos(double x);

        double cartesianSin(double x);

        double radianCos(double x);

        double radianSin(double x);

        double getAngle(double ax, double ay, double bx, double by);

        double getDistance(double ax, double ay, double bx, double by);
    }

    template <class R = float, class A>
    R toRadians(A angle) {
        return static_cast<R>(angle * PI_OVER_180);
    }

    template <class R = float, class A>
    R toCartesian(A angle) {
        return static_cast<R>(angle * PI_UNDER_180);
    }

    template <class R = float, class A>
    R cartesianCos(A angle) {
        return static_cast<R>(detail::cartesianCos(angle));
    }

    template <typename R = float, typename A>
    R radianCos(A angle) {
        return static_cast<R>(detail::radianCos(angle));
    }

    template <typename R = float, typename A>
    R radianSin(A angle) {
        return static_cast<R>(detail::radianSin(angle));
    }

    template <class R = float, class A>
    R cartesianSin(A angle) {
        return static_cast<R>(detail::cartesianSin(angle));
    }

    template <class R = float, class A, class B>
    R getDistance(A ax, A ay, B bx, B by) {
        return static_cast<R>(detail::getDistance(ax, ay, bx, by));
    }

    template <class R = float, class A, class B>
    R getAngle(A ax, A ay, B bx, B by) {
        return static_cast<R>(detail::getAngle(ax, ay, bx, by));
    }
}
