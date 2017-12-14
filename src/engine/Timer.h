//
// Created by ts14ic on 12/14/17.
//

#pragma once

class Clock;

class Timer {
public:
    Timer();

    void restart(const Clock& clock);

    unsigned long getStartTime() const;

    unsigned long getTicksSinceRestart(const Clock& clock) const;

    bool haveTicksPassedSinceStart(const Clock& clock, unsigned long ticks) const;

private:
    unsigned long mStartTime;
};
