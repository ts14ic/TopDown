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

    MouseEvent();

    Type get_type() const;

    float get_scroll_amount() const;

    float get_x() const;

    float get_y() const;

    void set_type(Type type);

    void set_scroll_amount(float scrollAmount);

    void set_x(float x);

    void set_y(float y);

private:
    Type _type;
    float _scroll_amount;
    float _x;
    float _y;
};
