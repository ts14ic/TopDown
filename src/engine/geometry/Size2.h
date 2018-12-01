#pragma once

#include <type_traits>

template<typename SizeT = int, typename = std::enable_if_t<std::is_arithmetic<SizeT>{}>>
class Size2 {
public:
    Size2() {
        width = 0;
        height = 0;
    }

    Size2(SizeT width, SizeT height) {
        this->width = width;
        this->height = height;
    }

    SizeT get_width() const {
        return width;
    }

    void set_width(SizeT width) {
        if (width >= 0) this->width = width;
    }

    SizeT get_height() const {
        return height;
    }

    void set_height(SizeT height) {
        if (height >= 0) { this->height = height; }
    }

private:
    SizeT width;
    SizeT height;
};

template<typename SizeT = int, typename = std::enable_if_t<std::is_arithmetic<SizeT>{}>>
Size2<SizeT> make_size(SizeT width, SizeT height) {
    return Size2<SizeT>{width, height};
}

template<typename ToType, typename FromType>
Size2<ToType> size_cast(Size2<FromType> from) {
    return make_size(static_cast<ToType>(from.width), static_cast<ToType>(from.height));
}
