#pragma once

class StopWatch {
public:
    StopWatch();

    void start();
    unsigned get_ticks() const;
    bool passed(unsigned ticks) const;
private:
    unsigned _startedAt;
};
