#pragma once

#include "MouseEvent.h"

class MouseEventHandler {
public:
    virtual ~MouseEventHandler() = 0;

    virtual void handle_mouse_event(const MouseEvent &event) = 0;
};
