#pragma once

#include <type_traits>

template <typename CoordT = int, typename = std::enable_if_t<std::is_arithmetic<CoordT>{}>>
struct Point2 {
    Point2() {
        x = 0;
        y = 0;
    }

    Point2(CoordT x, CoordT y) {
        this->x = x;
        this->y = y;
    }

    CoordT x;
    CoordT y;
};

template <typename CoordT>
Point2<CoordT> make_point(CoordT x, CoordT y) {
    return Point2<CoordT>{x, y};
}

template <typename ToType, typename FromType>
Point2<ToType> point_cast(Point2<FromType> from) {
    return make_point(static_cast<ToType>(from.x), static_cast<ToType>(from.y));
}
