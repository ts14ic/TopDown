#pragma once

#include <engine/clock/Clock.h>

class Timer {
public:
    Timer();

    void restart(const Clock& clock);

    unsigned long get_start_time() const;

    unsigned long get_ticks_since_start(const Clock& clock) const;

    bool ticks_passed_since_start(const Clock& clock, unsigned long ticks) const;

private:
    unsigned long _start_time;
};
