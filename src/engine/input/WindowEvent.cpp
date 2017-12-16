//
// Created by ts14ic on 12/15/17.
//

#include "WindowEvent.h"

WindowEvent::WindowEvent() = default;

WindowEvent::Type WindowEvent::getType() const {
    return mType;
}

void WindowEvent::setType(WindowEvent::Type type) {
    mType = type;
}
