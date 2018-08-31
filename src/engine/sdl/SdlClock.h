#pragma once

#include "engine/Clock.h"

class SdlClock : public Clock {
public:
    unsigned long getCurrentTime() const override;
};
