#pragma once

#include "WindowEvent.h"

class WindowEventHandler {
public:
    virtual ~WindowEventHandler() = 0;

    virtual void handle_window_event(const WindowEvent& event) = 0;
};
