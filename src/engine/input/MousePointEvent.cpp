//
// Created by ts14ic on 01/09/18.
//

#include "MousePointEvent.h"

MousePointEvent::MousePointEvent(MousePointEvent::Type type, int x, int y) {
    _type = type;
    _x = x;
    _y = y;
}

MousePointEvent::Type MousePointEvent::get_type() const {
    return _type;
}

int MousePointEvent::get_x() const {
    return _x;
}

int MousePointEvent::get_y() const {
    return _y;
}


