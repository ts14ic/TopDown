//
// Created by ts14ic on 12/14/17.
//

#pragma once

#include "../engine/Clock.h"

class SdlClock : public Clock {
public:
    unsigned long getCurrentTime() const override;
};
