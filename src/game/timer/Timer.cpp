#include "Timer.h"

Timer::Timer()
        : _start_time{} {
}

void Timer::restart(const Clock& clock) {
    _start_time = clock.get_current_time();
}

unsigned long Timer::get_start_time() const {
    return _start_time;
}

unsigned long Timer::get_ticks_since_start(const Clock &clock) const {
    return clock.get_current_time() - _start_time;
}

bool Timer::ticks_passed_since_start(const Clock& clock, unsigned long ticks) const {
    return get_ticks_since_start(clock) >= ticks;
}
