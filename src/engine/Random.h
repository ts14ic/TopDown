//
// Created by ts14ic on 12/12/17.
//
#pragma once

#include <random>

class Random {
public:
    Random();

    int getInt();

    int getInt(int min, int max);

    float getFloat(float min = 0.f, float max = 1.f);

private:
    std::mt19937 mRandomEngine;
};
