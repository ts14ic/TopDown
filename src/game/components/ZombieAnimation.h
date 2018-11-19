#pragma once

#include <game/timer/Timer.h>

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

    Timer get_timer() const {
        return _timer;
    }

    void reset_timer(const Clock& clock) {
        _timer.restart(clock);
    }

private:
    int _frame = 0;
    Timer _timer;
};
