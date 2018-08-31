#include "MouseEvent.h"

MouseEvent::MouseEvent() = default;

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

void MouseEvent::set_type(MouseEvent::Type type) {
    _type = type;
}

void MouseEvent::set_scroll_amount(float scrollAmount) {
    _scroll_amount = scrollAmount;
}

void MouseEvent::set_x(float x) {
    _x = x;
}

void MouseEvent::set_y(float y) {
    _y = y;
}
