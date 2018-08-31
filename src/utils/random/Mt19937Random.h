#pragma once

#include "engine/Random.h"
#include <random>

class Mt19937Random : public Random {
public:
    Mt19937Random();

    int get_int() const override;

    int get_int(int min, int max) const override;

    std::size_t get_size_t() const override;

    std::size_t get_size_t(std::size_t min, std::size_t max) const override;

    float get_float() const override;

    float get_float(float min, float max) const override;

private:
    mutable std::mt19937 _random_engine;
};

