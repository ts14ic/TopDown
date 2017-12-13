//
// Created by ts14ic on 12/13/17.
//

#pragma once

class Box {
public:
    Box();

    Box(float x, float y, float width, float height);

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    void setPosition(float x, float y);

    float getWidth() const;

    void setWidth(float width);

    float getHeight() const;

    void setHeight(float height);

    void setSize(float width, float height);

    void set(float x, float y, float width, float height);

private:
    float mX;
    float mY;
    float mWidth;
    float mHeight;
};
