//
// Created by ts14ic on 12/11/17.
//

#pragma once

class Circle {
public:
    Circle();

    Circle(int x, int y, int r);

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    int getRadius() const;

    void setRadius(int r);

private:
    int mX;
    int mY;
    int mRadius;
};

bool circlesCollide(Circle const& a, Circle const& b);
