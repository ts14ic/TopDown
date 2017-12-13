//
// Created by ts14ic on 12/13/17.
//

#include <cmath>
#include "Box.h"

Box::Box()
        : Box{0, 0, 0, 0} {

}

Box::Box(float x, float y, float width, float height)
        : mX{x}, mY{y}, mWidth{width}, mHeight{height} {

}

float Box::getX() const {
    return mX;
}

void Box::setX(float x) {
    mX = x;
}

float Box::getY() const {
    return mY;
}

void Box::setY(float y) {
    mY = y;
}

float Box::getWidth() const {
    return mWidth;
}

void Box::setWidth(float width) {
    if(std::isgreaterequal(width, 0)) {
        mWidth = width;
    }
}

float Box::getHeight() const {
    return mHeight;
}

void Box::setHeight(float height) {
    if(std::isgreaterequal(height, 0)) {
        mHeight = height;
    }
}

void Box::setPosition(float x, float y) {
    setX(x);
    setY(y);
}

void Box::setSize(float width, float height) {
    setWidth(width);
    setHeight(height);
}

void Box::set(float x, float y, float width, float height) {
    setPosition(x, y);
    setSize(width, height);
}
