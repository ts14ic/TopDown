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

size_t Mt19937Random::getSize() const {
    return getSize(0, std::numeric_limits<std::size_t>::max());
}

size_t Mt19937Random::getSize(std::size_t min, std::size_t max) const {
    std::uniform_int_distribution<std::size_t> dis(min, max);
    return dis(mRandomEngine);
}

float Mt19937Random::getFloat() const {
    return getFloat(0.f, 1.f);
}

float Mt19937Random::getFloat(float min, float max) const {
    std::uniform_real_distribution<float> dis(min, max);
    return dis(mRandomEngine);
}
