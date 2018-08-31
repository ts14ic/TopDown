#pragma once

#include "EventHandler.h"

class InputContext {
public:
    virtual ~InputContext() = 0;

    virtual void poll_events(EventHandler &eventHandler) = 0;

protected:
    virtual void forward_window_event(WindowEventHandler &eventHandler) = 0;

    virtual void forward_mouse_event(MouseEventHandler &eventHandler) = 0;

    virtual void forward_keyboard_event(KeyboardEventHandler &eventHandler) = 0;
};
