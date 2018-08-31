#pragma once

#include "MouseEvent.h"

class MouseEventHandler {
public:
    virtual ~MouseEventHandler() = 0;

    virtual void handleMouseEvent(const MouseEvent& event) = 0;
};
