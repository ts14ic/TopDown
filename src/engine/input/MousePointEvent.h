#pragma once

class MousePointEvent {
public:
    enum class Type {
        Motion,
        ButtonUp,
        ButtonDown
    };

    MousePointEvent(Type type, int x, int y);

    Type get_type() const;

    int get_x() const;

    int get_y() const;

private:
    Type _type;
    int _x;
    int _y;
};