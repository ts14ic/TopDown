#include "Circle.h"
#include "utils/math/math.h"

Circle::Circle() = default;

Circle::Circle(float x, float y, float r)
        : mX(x), mY(y), mRadius(r) {}

float Circle::getX() const {
    return mX;
}

void Circle::setX(float x) {
    Circle::mX = x;
}

float Circle::getY() const {
    return mY;
}

void Circle::setY(float y) {
    Circle::mY = y;
}

float Circle::getRadius() const {
    return mRadius;
}

void Circle::setRadius(float r) {
    Circle::mRadius = r;
}

bool circlesCollide(Circle const& a, Circle const& b) {
    return math::getDistance(a.getX(), a.getY(), b.getX(), b.getY()) < (a.getRadius() + b.getRadius());
}
