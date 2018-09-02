#pragma once

class MouseScrollEvent {
public:
    enum class Type {
        SCROLL_DOWN,
        SCROLL_UP,
    };

    MouseScrollEvent(Type type, int scroll);

    Type get_type() const;

    int get_scroll_amount() const;

private:
    Type _type;
    int _scroll_amount;
};
