//
// Created by ts14ic on 12/12/17.
//
#pragma once

class Random {
public:
    virtual int getInt() = 0;

    virtual int getInt(int min, int max) = 0;

    virtual float getFloat() = 0;

    virtual float getFloat(float min, float max) = 0;

    virtual ~Random() = 0;
};
