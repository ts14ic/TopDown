#pragma once

#include <type_traits>

template <typename SizeT = int, typename = std::enable_if_t<std::is_arithmetic<SizeT>{}>>
struct Size2 {
    Size2() {
        width = 0;
        height = 0;
    }

    Size2(SizeT width, SizeT height) {
        this->width = width;
        this->height = height;
    }

    SizeT width;
    SizeT height;
};

template <typename SizeT = int, typename = std::enable_if_t<std::is_arithmetic<SizeT>{}>>
Size2<SizeT> make_size(SizeT width, SizeT height) {
    return Size2<SizeT>{width, height};
}

template <typename ToType, typename FromType>
Size2<ToType> size_cast(Size2<FromType> from) {
    return make_size(static_cast<ToType>(from.width), static_cast<ToType>(from.height));
}
