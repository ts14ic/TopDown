#pragma once

class Box {
public:
    Box();

    Box(float x, float y, float width, float height);

    float getX() const;

    float getY() const;

    float getWidth() const;

    float getHeight() const;

    void setX(float x);

    void setY(float y);

    void setPosition(float x, float y);

    void setWidth(float width);

    void setHeight(float height);

    void setSize(float width, float height);

    void set(float x, float y, float width, float height);

private:
    float mX;
    float mY;
    float mWidth;
    float mHeight;
};
