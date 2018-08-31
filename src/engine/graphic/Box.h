#pragma once

class Box {
public:
    Box();

    Box(float x, float y, float width, float height);

    float get_x() const;

    float get_y() const;

    float get_width() const;

    float get_height() const;

    void set_x(float x);

    void set_y(float y);

    void set_position(float x, float y);

    void set_width(float width);

    void set_height(float height);

    void set_sizes(float width, float height);
private:
    float _x;
    float _y;
    float _width;
    float _height;
};
