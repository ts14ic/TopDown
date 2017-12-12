//
// Created by ts14ic on 12/12/17.
//

#include <iostream>
#include "Random.h"

Random::Random()
        : mRandomEngine{std::default_random_engine{}()} {}

int Random::getInt() {
    return getInt(0, std::numeric_limits<int>::max());
}

int Random::getInt(int min, int max) {
    std::uniform_int_distribution<int> dis(min, max);
    return dis(mRandomEngine);
}

float Random::getFloat(float min, float max) {
    std::uniform_real_distribution<float> dis(min, max);
    return dis(mRandomEngine);
}
