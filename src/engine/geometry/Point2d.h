#pragma once

#include <type_traits>

template <typename CoordT = int, typename = std::enable_if_t<std::is_arithmetic<CoordT>{}>>
struct Point2d {
    Point2d() {
        x = 0;
        y = 0;
    }

    Point2d(CoordT x, CoordT y) {
        this->x = x;
        this->y = y;
    }

    CoordT x;
    CoordT y;
};

template <typename CoordT>
Point2d<CoordT> make_point(CoordT x, CoordT y) {
    return Point2d<CoordT>{x, y};
}

template <typename ToType, typename FromType>
Point2d<ToType> point_cast(Point2d<FromType> from) {
    return make_point(static_cast<ToType>(from.x), static_cast<ToType>(from.y));
}
