#pragma once

#include <engine/geometry/Point2d.h>

class MousePointEvent {
public:
    enum class Type {
        MOTION,
        BUTTON_UP,
        BUTTON_DOWN
    };

    MousePointEvent(Type type, Point2d<int> position) {
        _type = type;
        _position = position;
    }

    Type get_type() const { return _type; }

    Point2d<int> get_position() const { return _position; }

private:
    Type _type;
    Point2d<int> _position;
};