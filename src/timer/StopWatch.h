#pragma once

class StopWatch {
public:
    StopWatch();

    void restart();

    unsigned getTicks() const;

    bool ticksHavePassed(unsigned ticks) const;
private:
    unsigned _startedAt;
};
