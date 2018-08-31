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

    void set_type(Type type);

    float get_scroll_amount() const;

    void set_scroll_amount(float scrollAmount);

    float get_x() const;

    void set_x(float x);

    float get_y() const;

    void set_y(float y);

private:
    Type _type;
    float _scroll_amount;
    float _x;
    float _y;
};
