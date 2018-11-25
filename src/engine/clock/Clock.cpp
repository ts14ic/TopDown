#include "Clock.h"
#include <engine/log/Log.h>
#include <cassert>

class NullClockEngine : public ClockEngine {
public:
    std::size_t get_current_time() const override {
        Log::w("Clock engine not installed, NullClockEngine used instead");
        return 0;
    }
};

static std::unique_ptr<ClockEngine> CLOCK_ENGINE = std::make_unique<NullClockEngine>();

void Clock::install_clock_engine(std::unique_ptr<ClockEngine> clock_engine) {
    assert(clock_engine != nullptr && "Can't use nullptr for clock engine");
    CLOCK_ENGINE = std::move(clock_engine);
}

void Clock::uninstall_clock_engine() {
    CLOCK_ENGINE = std::make_unique<NullClockEngine>();
}

std::size_t Clock::get_current_time() {
    return CLOCK_ENGINE->get_current_time();
}
