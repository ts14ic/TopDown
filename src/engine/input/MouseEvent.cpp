#include "MouseEvent.h"

MouseEvent::MouseEvent() = default;

MouseEvent::Type MouseEvent::get_type() const {
    return _type;
}

void MouseEvent::set_type(MouseEvent::Type type) {
    _type = type;
}

float MouseEvent::get_scroll_amount() const {
    return _scroll_amount;
}

void MouseEvent::set_scroll_amount(float scrollAmount) {
    _scroll_amount = scrollAmount;
}

float MouseEvent::get_x() const {
    return _x;
}

void MouseEvent::set_x(float x) {
    _x = x;
}

float MouseEvent::get_y() const {
    return _y;
}

void MouseEvent::set_y(float y) {
    _y = y;
}
