#include "Color.h"

Color::Color()
        : Color{0, 0, 0, 255} {

}

Color::Color(int red, int green, int blue, int alpha)
        : _red{red}, _green{green}, _blue{blue}, _alpha{alpha} {

}

int Color::get_red() const {
    return _red;
}

void Color::set_red(int red) {
    _red = red;
}

int Color::get_green() const {
    return _green;
}

void Color::set_green(int green) {
    _green = green;
}

int Color::get_blue() const {
    return _blue;
}

void Color::set_blue(int blue) {
    _blue = blue;
}

int Color::get_alpha() const {
    return _alpha;
}

void Color::set_alpha(int alpha) {
    _alpha = alpha;
}
