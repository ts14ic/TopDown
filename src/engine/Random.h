//
// Created by ts14ic on 12/12/17.
//
#pragma once

#include <cstddef>

class Random {
public:
    virtual int getInt() const = 0;

    virtual int getInt(int min, int max) const = 0;

    virtual std::size_t getSize() const = 0;

    virtual std::size_t getSize(std::size_t min, std::size_t max) const = 0;

    virtual float getFloat() const = 0;

    virtual float getFloat(float min, float max) const = 0;

    virtual ~Random() = 0;
};
