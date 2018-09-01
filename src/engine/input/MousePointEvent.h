#pragma once

#include "engine/geometry/Point2.h"

class MousePointEvent {
public:
    enum class Type {
        Motion,
        ButtonUp,
        ButtonDown
    };

    MousePointEvent(Type type, Point2<int> position) {
        _type = type;
        _position = position;
    }

    Type get_type() const { return _type; }

    Point2<int> get_position() const { return _position; }

private:
    Type _type;
    Point2<int> _position;
};