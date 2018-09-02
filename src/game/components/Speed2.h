#pragma once

#include <type_traits>

template <typename CoordT = int, typename = std::enable_if_t<std::is_arithmetic<CoordT>{}>>
struct Speed2 {
    Speed2() {
        x = 0;
        y = 0;
    }

    Speed2(CoordT x, CoordT y) {
        this->x = x;
        this->y = y;
    }

    CoordT x;
    CoordT y;
};

template <typename CoordT>
Speed2<CoordT> make_speed(CoordT x, CoordT y) {
    return Speed2<CoordT>{x, y};
}

template <typename ToType, typename FromType>
Speed2<ToType> speed_cast(Speed2<FromType> from) {
    return make_speed(static_cast<ToType>(from.x), static_cast<ToType>(from.y));
}
