#include "WindowEvent.h"

WindowEvent::WindowEvent() = default;

WindowEvent::Type WindowEvent::get_type() const {
    return mType;
}

void WindowEvent::set_type(WindowEvent::Type type) {
    mType = type;
}
