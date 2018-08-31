#include "Circle.h"
#include "math/maths.h"

Circle::Circle() = default;

Circle::Circle(float x, float y, float r)
        : _x(x), _y(y), _radius(r) {}

float Circle::get_x() const {
    return _x;
}

void Circle::set_x(float x) {
    Circle::_x = x;
}

float Circle::get_y() const {
    return _y;
}

void Circle::set_y(float y) {
    Circle::_y = y;
}

float Circle::get_radius() const {
    return _radius;
}

void Circle::set_radius(float r) {
    Circle::_radius = r;
}

bool circles_collide(Circle const &lhs, Circle const &rhs) {
    return math::get_distance(lhs.get_x(), lhs.get_y(), rhs.get_x(), rhs.get_y()) < (lhs.get_radius() + rhs.get_radius());
}
