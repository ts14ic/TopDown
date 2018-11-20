#pragma once

#include <game/timer/Timer.h>
#include <cstddef>

class ZombieAnimation {
public:
    int get_frame() const {
        return _frame;
    }

    void next_frame() {
        ++_frame;
    }

    void reset_frame() {
        _frame = 0;
    }

    bool ticks_passed_since_start(const Clock& clock, std::size_t ticks) const {
        return _timer.ticks_passed_since_start(clock, ticks);
    }

    void reset_timer(const Clock& clock) {
        _timer.restart(clock);
    }

private:
    int _frame = 0;
    Timer _timer;
};
