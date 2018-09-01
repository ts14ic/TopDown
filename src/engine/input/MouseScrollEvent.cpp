#include "MouseScrollEvent.h"

MouseScrollEvent::MouseScrollEvent(MouseScrollEvent::Type type, int scroll) {
    _type = type;
    _scroll_amount = scroll;
}

MouseScrollEvent::Type MouseScrollEvent::get_type() const {
    return _type;
}

int MouseScrollEvent::get_scroll_amount() const {
    return _scroll_amount;
}
