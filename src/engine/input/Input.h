#pragma once

#include "EventHandler.h"

class Input {
public:
    virtual ~Input() = 0;

    virtual void poll_events(EventHandler &eventHandler) = 0;
};
