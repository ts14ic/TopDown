#pragma once

#include "WindowEvent.h"

class WindowEventHandler {
public:
    virtual ~WindowEventHandler() = 0;

    virtual void handleWindowEvent(const WindowEvent& event) = 0;
};
