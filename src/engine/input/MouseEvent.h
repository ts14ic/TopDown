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

    Type getType() const;

    float getScrollAmount() const;

    float getX() const;

    float getY() const;

    void setType(Type type);

    void setScrollAmount(float scrollAmount);

    void setX(float x);

    void setY(float y);

private:
    Type mType;
    float mScrollAmount;
    float mX;
    float mY;
};
