#pragma once

#include "Point2.h"
#include "Size2.h"

class Box {
public:
    Box() = default;

    Box(Point2<float> left_top, Size2<float> size) {
        _left_top = left_top;
        _size = size;
    }

    Point2<float> get_left_top() const { return _left_top; }

    void set_left_top(Point2<float> left_top) { _left_top = left_top; }

    void set_left_top(float x, float y) {
        set_left_top(make_point(x, y));
    }

    void set_left_top_x(float x) {
        _left_top.x = x;
    }

    void set_left_top_y(float y) {
        _left_top.y = y;
    }

    Size2<float> get_size() const { return _size; }

    float get_width() const { return _size.get_width(); }

    void set_width(float width) { _size.set_width(width); }

    float get_height() const { return _size.get_height(); }

    void set_height(float height) { _size.set_height(height); }

    void set_size(Size2<float> size) {
        _size = size;
    }

    void set_size(float width, float height) {
        set_size(make_size(width, height));
    }

private:
    Point2<float> _left_top;
    Size2<float> _size;
};
