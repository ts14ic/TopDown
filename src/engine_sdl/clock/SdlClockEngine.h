#pragma once

#include <engine/clock/ClockEngine.h>

class SdlClockEngine : public ClockEngine {
public:
    std::size_t get_current_time() const override;
};
