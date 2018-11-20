#include "Timer.h"

Timer::Timer()
        : _start_time{} {
}

void Timer::restart() {
    _start_time = Clock::get_current_time();
}

std::size_t Timer::get_start_time() const {
    return _start_time;
}

std::size_t Timer::get_ticks_since_start() const {
    return Clock::get_current_time() - _start_time;
}

bool Timer::ticks_passed_since_start(std::size_t ticks) const {
    return get_ticks_since_start() >= ticks;
}
