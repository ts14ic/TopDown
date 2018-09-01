#include "WindowEvent.h"

WindowEvent::WindowEvent(Type type) {
    _type = type;
}

WindowEvent::Type WindowEvent::get_type() const {
    return _type;
}
