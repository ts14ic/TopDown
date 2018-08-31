#include "WindowEvent.h"

WindowEvent::WindowEvent() = default;

WindowEvent::Type WindowEvent::getType() const {
    return mType;
}

void WindowEvent::setType(WindowEvent::Type type) {
    mType = type;
}
