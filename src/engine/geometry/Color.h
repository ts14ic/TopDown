#pragma once

class Color {
public:
    Color();

    Color(int red, int green, int blue, int alpha = 255);

    int get_red() const;

    void set_red(int red);

    int get_green() const;

    void set_green(int green);

    int get_blue() const;

    void set_blue(int blue);

    int get_alpha() const;

    void set_alpha(int alpha);

private:
    int _red;
    int _green;
    int _blue;
    int _alpha;
};
