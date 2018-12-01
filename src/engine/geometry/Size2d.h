#pragma once

#include <type_traits>
#include <cassert>

template<typename SizeT = int, typename = std::enable_if_t<std::is_arithmetic<SizeT>{}>>
class Size2d {
public:
    Size2d() {
        width = 0;
        height = 0;
    }

    Size2d(SizeT width, SizeT height) {
        assert(width >= 0 && height >= 0);
        this->width = width;
        this->height = height;
    }

    SizeT get_width() const {
        return width;
    }

    void set_width(SizeT width) {
        assert(width >= 0);
        if (width >= 0) {
            this->width = width;
        }
    }

    SizeT get_height() const {
        return height;
    }

    void set_height(SizeT height) {
        assert(height >= 0);
        if (height >= 0) {
            this->height = height;
        }
    }

private:
    SizeT width;
    SizeT height;
};

template<typename SizeT = int, typename = std::enable_if_t<std::is_arithmetic<SizeT>{}>>
Size2d<SizeT> make_size(SizeT width, SizeT height) {
    return Size2d<SizeT>{width, height};
}

template<typename ToType, typename FromType>
Size2d<ToType> size_cast(Size2d<FromType> from) {
    return make_size(static_cast<ToType>(from.width), static_cast<ToType>(from.height));
}
