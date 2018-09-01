#pragma once

class MouseEvent {
public:
    enum class Type {
        Motion,
        ButtonDown,
        ButtonUp,
        ScrollDown,
        ScrollUp,
    };

    MouseEvent(Type type, float x, float y);

    MouseEvent(Type type, float scroll);

    Type get_type() const;

    float get_scroll_amount() const;

    float get_x() const;

    float get_y() const;

private:
    Type _type;
    float _scroll_amount;
    float _x;
    float _y;
};
