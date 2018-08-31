#pragma once

#include "engine/Clock.h"

class SdlClock : public Clock {
public:
    unsigned long get_current_time() const override;
};
