#include "MouseEvent.h"

MouseEvent::MouseEvent(MouseEvent::Type type, float x, float y) {
    _type = type;
    _x = x;
    _y = y;

    _scroll_amount = 0;
}

MouseEvent::MouseEvent(MouseEvent::Type type, float scroll) {
    _type = type;
    _scroll_amount = scroll;

    _x = 0;
    _y = 0;
}

MouseEvent::Type MouseEvent::get_type() const {
    return _type;
}

float MouseEvent::get_scroll_amount() const {
    return _scroll_amount;
}

float MouseEvent::get_x() const {
    return _x;
}

float MouseEvent::get_y() const {
    return _y;
}
