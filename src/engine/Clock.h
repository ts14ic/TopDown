#pragma once

class Clock {
public:
    virtual ~Clock() = 0;

    virtual unsigned long get_current_time() const = 0;
};
