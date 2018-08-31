//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "../input/InputContext.h"
#include "../input/MouseEvent.h"
#include "../input/KeyboardEvent.h"
#include "../input/WindowEvent.h"
#include "../input/EventHandler.h"
#include <SDL_events.h>

class SdlInputContext : public InputContext {
public:
    void pollEvents(EventHandler& eventHandler) override;

private:
    void forwardWindowEvent(WindowEventHandler& eventHandler) override;

    void forwardMouseEvent(MouseEventHandler& eventHandler) override;

    void forwardKeyboardEvent(KeyboardEventHandler& eventHandler) override;

private:
    WindowEvent mWindowEvent;
    MouseEvent mMouseEvent;
    KeyboardEvent mKeyEvent;
};
