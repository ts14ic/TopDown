//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "../engine/Random.h"
#include <random>

class Mt19937Random : public Random {
public:
    Mt19937Random();

    int getInt() override;

    int getInt(int min, int max) override;

    float getFloat() override;

    float getFloat(float min, float max) override;

private:
    std::mt19937 mRandomEngine;
};

