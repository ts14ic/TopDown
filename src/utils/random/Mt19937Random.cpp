//
// Created by ts14ic on 12/13/17.
//

#include "Mt19937Random.h"

Mt19937Random::Mt19937Random()
        : mRandomEngine{std::default_random_engine{}()} {}

int Mt19937Random::getInt() const {
    return getInt(0, std::numeric_limits<int>::max());
}

int Mt19937Random::getInt(int min, int max) const {
    std::uniform_int_distribution<int> dis(min, max);
    return dis(mRandomEngine);
}

float Mt19937Random::getFloat() const {
    return getFloat(0.f, 1.f);
}

float Mt19937Random::getFloat(float min, float max) const {
    std::uniform_real_distribution<float> dis(min, max);
    return dis(mRandomEngine);
}
