#pragma once

#include <cstddef>

class Random {
public:
    virtual int get_int() const = 0;

    virtual int get_int(int min, int max) const = 0;

    virtual std::size_t get_size_t() const = 0;

    virtual std::size_t get_size_t(std::size_t min, std::size_t max) const = 0;

    virtual float get_float() const = 0;

    virtual float get_float(float min, float max) const = 0;

    virtual ~Random() = 0;
};
