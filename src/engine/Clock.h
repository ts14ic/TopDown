//
// Created by ts14ic on 12/14/17.
//
#pragma once

class Clock {
public:
    virtual ~Clock() = 0;

    virtual unsigned long getCurrentTime() const = 0;
};
