#pragma once

#include "EventHandler.h"

class Input {
public:
    virtual ~Input() = 0;

    virtual void set_event_handler(EventHandler& eventHandler) = 0;

    virtual void remove_event_handler() = 0;

    virtual void poll_events() = 0;
};
