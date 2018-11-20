#include "Clock.h"
#include <cassert>

static std::unique_ptr<ClockEngine> CLOCK_ENGINE;

void Clock::install_clock_engine(std::unique_ptr<ClockEngine> clock_engine) {
    CLOCK_ENGINE = std::move(clock_engine);
}

void Clock::uninstall_clock_engine() {
    CLOCK_ENGINE = nullptr;
}

std::size_t Clock::get_current_time() {
    assert(CLOCK_ENGINE != nullptr && "must install a clock engine");
    return CLOCK_ENGINE->get_current_time();
}
