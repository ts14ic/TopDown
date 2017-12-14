//
// Created by ts14ic on 12/13/17.
//

#pragma once

class Color {
public:
    Color();

    Color(int red, int green, int blue, int alpha = 255);

    int getRed() const;

    int getGreen() const;

    int getBlue() const;

    int getAlpha() const;

    void setRed(int red);

    void setGreen(int green);

    void setBlue(int blue);

    void setAlpha(int alpha);

private:
    int mRed;
    int mGreen;
    int mBlue;
    int mAlpha;
};
