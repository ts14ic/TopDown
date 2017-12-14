//
// Created by ts14ic on 12/12/17.
//
#pragma once

class Random {
public:
    virtual int getInt() const = 0;

    virtual int getInt(int min, int max) const = 0;

    virtual float getFloat() const = 0;

    virtual float getFloat(float min, float max) const = 0;

    virtual ~Random() = 0;
};
