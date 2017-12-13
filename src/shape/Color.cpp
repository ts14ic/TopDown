//
// Created by ts14ic on 12/13/17.
//

#include "Color.h"

Color::Color()
        : Color{0, 0, 0, 255} {

}

Color::Color(int red, int green, int blue, int alpha)
        : mRed{red}, mGreen{green}, mBlue{blue}, mAlpha{alpha} {

}

int Color::getRed() const {
    return mRed;
}

void Color::setRed(int red) {
    mRed = red;
}

int Color::getGreen() const {
    return mGreen;
}

void Color::setGreen(int green) {
    mGreen = green;
}

int Color::getBlue() const {
    return mBlue;
}

void Color::setBlue(int blue) {
    mBlue = blue;
}

int Color::getAlpha() const {
    return mAlpha;
}

void Color::setAlpha(int alpha) {
    mAlpha = alpha;
}
