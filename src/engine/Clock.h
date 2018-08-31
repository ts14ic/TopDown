#pragma once

class Clock {
public:
    virtual ~Clock() = 0;

    virtual unsigned long getCurrentTime() const = 0;
};
