#pragma once

class Circle {
public:
    Circle();

    Circle(float x, float y, float radius);

    float get_x() const;

    void set_x(float x);

    float get_y() const;

    void set_y(float y);

    float get_radius() const;

    void set_radius(float radius);

private:
    float _x;
    float _y;
    float _radius;
};

bool circles_collide(const Circle& lhs, const Circle& rhs);
