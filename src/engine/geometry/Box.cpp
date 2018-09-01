#include <cmath>
#include "Box.h"

float Box::get_width() const {
    return _width;
}

void Box::set_width(float width) {
    if(width >= 0) {
        _width = width;
    }
}

float Box::get_height() const {
    return _height;
}

void Box::set_height(float height) {
    if(_width >= 0) {
        _height = height;
    }
}

void Box::set_sizes(float width, float height) {
    set_width(width);
    set_height(height);
}
