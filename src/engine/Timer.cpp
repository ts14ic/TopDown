//
// Created by ts14ic on 12/14/17.
//

#include "Timer.h"
#include "Clock.h"

Timer::Timer()
        : mStartTime{} {
}

void Timer::restart(const Clock& clock) {
    mStartTime = clock.getCurrentTime();
}

unsigned long Timer::getStartTime() const {
    return mStartTime;
}

unsigned long Timer::getTicksSinceRestart(const Clock& clock) const {
    return clock.getCurrentTime() - mStartTime;
}

bool Timer::haveTicksPassedSinceStart(const Clock& clock, unsigned long ticks) const {
    return getTicksSinceRestart(clock) >= ticks;
}
