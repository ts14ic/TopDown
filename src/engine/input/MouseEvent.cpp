//
// Created by ts14ic on 12/15/17.
//

#include "MouseEvent.h"

MouseEvent::MouseEvent() = default;

MouseEvent::Type MouseEvent::getType() const {
    return mType;
}

float MouseEvent::getScrollAmount() const {
    return mScrollAmount;
}

float MouseEvent::getX() const {
    return mX;
}

float MouseEvent::getY() const {
    return mY;
}

void MouseEvent::setType(MouseEvent::Type type) {
    mType = type;
}

void MouseEvent::setScrollAmount(float scrollAmount) {
    mScrollAmount = scrollAmount;
}

void MouseEvent::setX(float x) {
    mX = x;
}

void MouseEvent::setY(float y) {
    mY = y;
}
