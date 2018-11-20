#pragma once

#include <engine/clock/Clock.h>

class Timer {
public:
    Timer();

    void restart();

    std::size_t get_start_time() const;

    std::size_t get_ticks_since_start() const;

    bool ticks_passed_since_start(std::size_t ticks) const;

private:
    std::size_t _start_time;
};
