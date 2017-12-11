//
// Created by ts14ic on 12/11/17.
//

#pragma once

class Circle {
public:
    Circle();

    Circle(float x, float y, float radius);

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    float getRadius() const;

    void setRadius(float radius);

private:
    float mX;
    float mY;
    float mRadius;
};

bool circlesCollide(Circle const& a, Circle const& b);
