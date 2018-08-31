#include "Mt19937Random.h"

Mt19937Random::Mt19937Random()
        : _random_engine{std::default_random_engine{}()} {}

int Mt19937Random::get_int() const {
    return get_int(0, std::numeric_limits<int>::max());
}

int Mt19937Random::get_int(int min, int max) const {
    std::uniform_int_distribution<int> dis(min, max);
    return dis(_random_engine);
}

size_t Mt19937Random::get_size_t() const {
    return get_size_t(0, std::numeric_limits<std::size_t>::max());
}

size_t Mt19937Random::get_size_t(std::size_t min, std::size_t max) const {
    std::uniform_int_distribution<std::size_t> dis(min, max);
    return dis(_random_engine);
}

float Mt19937Random::get_float() const {
    return get_float(0.f, 1.f);
}

float Mt19937Random::get_float(float min, float max) const {
    std::uniform_real_distribution<float> dis(min, max);
    return dis(_random_engine);
}
