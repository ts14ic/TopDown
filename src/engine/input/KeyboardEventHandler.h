#pragma once

#include "KeyboardEvent.h"

class KeyboardEventHandler {
public:
    virtual ~KeyboardEventHandler() = 0;

    virtual void handle_key_event(const KeyboardEvent& event) = 0;
};
