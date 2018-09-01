#pragma once

#include "Point2.h"

class Circle {
public:
    Circle() = default;

    Circle(Point2<float> position, float radius) {
        _center_pos = position;
        _radius = radius;
    }

    Point2<float> get_center() const { return _center_pos; }

    void set_center(Point2<float> position) { _center_pos = position; }

    void set_center(float x, float y) {
        _center_pos = make_point(x, y);
    }

    void set_center_x(float x) {
        _center_pos.x = x;
    }

    void set_center_y(float y) {
        _center_pos.y = y;
    }

    float get_radius() const { return _radius; }

    void set_radius(float radius) { _radius = radius; }

private:
    Point2<float> _center_pos;
    float _radius = 0;
};

bool circles_collide(const Circle& lhs, const Circle& rhs);
