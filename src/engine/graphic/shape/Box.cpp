#include <cmath>
#include "Box.h"

Box::Box()
        : Box{0, 0, 0, 0} {
}

Box::Box(float x, float y, float width, float height)
        : _x{x}, _y{y}, _width{width}, _height{height} {
}

float Box::get_x() const {
    return _x;
}

void Box::set_x(float x) {
    _x = x;
}

float Box::get_y() const {
    return _y;
}

void Box::set_y(float y) {
    _y = y;
}

float Box::get_width() const {
    return _width;
}

void Box::set_width(float width) {
    if(std::isgreaterequal(width, 0)) {
        _width = width;
    }
}

float Box::get_height() const {
    return _height;
}

void Box::set_height(float height) {
    if(std::isgreaterequal(height, 0)) {
        _height = height;
    }
}

void Box::set_position(float x, float y) {
    set_x(x);
    set_y(y);
}

void Box::set_sizes(float width, float height) {
    set_width(width);
    set_height(height);
}
