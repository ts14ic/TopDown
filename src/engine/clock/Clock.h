#pragma once

#include "ClockEngine.h"
#include <memory>

class Clock {
public:
    Clock() = delete;

    static void install_clock_engine(std::unique_ptr<ClockEngine> clock_engine);

    static void uninstall_clock_engine();

    static std::size_t get_current_time();
};
