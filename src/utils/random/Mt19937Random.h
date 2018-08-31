#pragma once

#include "engine/Random.h"
#include <random>

class Mt19937Random : public Random {
public:
    Mt19937Random();

    int getInt() const override;

    int getInt(int min, int max) const override;

    std::size_t getSize() const override;

    std::size_t getSize(std::size_t min, std::size_t max) const override;

    float getFloat() const override;

    float getFloat(float min, float max) const override;

private:
    mutable std::mt19937 mRandomEngine;
};
