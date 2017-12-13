//
// Created by ts14ic on 12/13/17.
//

#pragma once

class Color {
public:
    Color();

    Color(int red, int green, int blue, int alpha = 255);

    int getRed() const;

    void setRed(int red);

    int getGreen() const;

    void setGreen(int green);

    int getBlue() const;

    void setBlue(int blue);

    int getAlpha() const;

    void setAlpha(int alpha);

private:
    int mRed;
    int mGreen;
    int mBlue;
    int mAlpha;
};
