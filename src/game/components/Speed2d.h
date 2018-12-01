#pragma once

#include <type_traits>

template <typename CoordT = int, typename = std::enable_if_t<std::is_arithmetic<CoordT>{}>>
struct Speed2d {
    Speed2d() {
        x = 0;
        y = 0;
    }

    Speed2d(CoordT x, CoordT y) {
        this->x = x;
        this->y = y;
    }

    CoordT x;
    CoordT y;
};

template <typename CoordT>
Speed2d<CoordT> make_speed(CoordT x, CoordT y) {
    return Speed2d<CoordT>{x, y};
}

template <typename ToType, typename FromType>
Speed2d<ToType> speed_cast(Speed2d<FromType> from) {
    return make_speed(static_cast<ToType>(from.x), static_cast<ToType>(from.y));
}
