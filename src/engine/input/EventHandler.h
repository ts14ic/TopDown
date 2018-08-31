#pragma once

#include "WindowEventHandler.h"
#include "MouseEventHandler.h"
#include "KeyboardEventHandler.h"

class EventHandler : public WindowEventHandler,
                     public MouseEventHandler,
                     public KeyboardEventHandler {
public:
};
