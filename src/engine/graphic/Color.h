#pragma once

class Color {
public:
    Color();

    Color(int red, int green, int blue, int alpha = 255);

    int get_red() const;

    int get_green() const;

    int get_blue() const;

    int get_alpha() const;

    void set_red(int red);

    void set_green(int green);

    void set_blue(int blue);

    void set_alpha(int alpha);

private:
    int _red;
    int _green;
    int _blue;
    int _alpha;
};
