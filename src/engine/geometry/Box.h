#pragma once

class Box {
public:
    Box();

    Box(float x, float y, float width, float height);

    float get_x() const;

    void set_x(float x);

    float get_y() const;

    void set_y(float y);

    void set_position(float x, float y);

    float get_width() const;

    void set_width(float width);

    float get_height() const;

    void set_height(float height);

    void set_sizes(float width, float height);
private:
    float _x;
    float _y;
    float _width;
    float _height;
};
