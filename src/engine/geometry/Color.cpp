#include "Color.h"
#include <cassert>

inline void set_component(int& component, int value) {
    assert(value >= 0 && value <= 255);
    component = value;
}

Color::Color() {
    _red = 0;
    _green = 0;
    _blue = 0;
    _alpha = 255;
}

Color::Color(int red, int green, int blue, int alpha) {
    set_component(_red, red);
    set_component(_green, green);
    set_component(_blue, blue);
    set_component(_alpha, alpha);
}

int Color::get_red() const {
    return _red;
}

void Color::set_red(int red) {
    set_component(_red, red);
}

int Color::get_green() const {
    return _green;
}

void Color::set_green(int green) {
    set_component(_green, green);
}

int Color::get_blue() const {
    return _blue;
}

void Color::set_blue(int blue) {
    set_component(_blue, blue);
}

int Color::get_alpha() const {
    return _alpha;
}

void Color::set_alpha(int alpha) {
    set_component(_alpha, alpha);
}
