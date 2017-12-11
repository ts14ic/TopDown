//
// Created by ts14ic on 12/11/17.
//

#include "Circle.h"
#include "calculations.h"

Circle::Circle() = default;

Circle::Circle(int x, int y, int r) : mX(x), mY(y), mRadius(r) {}

int Circle::getX() const {
    return mX;
}

void Circle::setX(int x) {
    Circle::mX = x;
}

int Circle::getY() const {
    return mY;
}

void Circle::setY(int y) {
    Circle::mY = y;
}

int Circle::getRadius() const {
    return mRadius;
}

void Circle::setRadius(int r) {
    Circle::mRadius = r;
}

bool circlesCollide(Circle const& a, Circle const& b) {
    return getDistance(a.getX(), a.getY(), b.getX(), b.getY()) < (a.getRadius() + b.getRadius());
}
