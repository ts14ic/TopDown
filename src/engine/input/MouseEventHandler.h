#pragma once

#include "MouseScrollEvent.h"
#include "MousePointEvent.h"

class MouseEventHandler {
public:
    virtual ~MouseEventHandler() = 0;

    virtual void handle_mouse_event(const MouseScrollEvent& event) = 0;

    virtual void handle_mouse_event(const MousePointEvent& event) = 0;
};
