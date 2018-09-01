#pragma once

#include "Point2.h"

class Box {
public:
    Box() = default;

    Box(Point2<float> left_top, float width, float height) {
        _left_top = left_top;
        _width = width;
        _height = height;
    }

    Point2<float> get_left_top() const { return _left_top; }

    void set_left_top(Point2<float> left_top) { _left_top = left_top; }

    void set_left_top(float x, float y) {
        _left_top = make_point(x, y);
    }

    void set_left_top_x(float x) {
        _left_top.x = x;
    }

    void set_left_top_y(float y) {
        _left_top.y = y;
    }

    float get_width() const;

    void set_width(float width);

    float get_height() const;

    void set_height(float height);

    void set_sizes(float width, float height);
private:
    Point2<float> _left_top;
    float _width = 0;
    float _height = 0;
};
