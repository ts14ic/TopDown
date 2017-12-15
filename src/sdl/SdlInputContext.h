//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "../event/InputContext.h"
#include <SDL_events.h>

class WindowEventHandler;

class MouseEventHandler;

class KeyboardEventHandler;

class EventHandler;

class SdlInputContext : public InputContext {
public:
    void pollEvents(EventHandler &eventHandler) override;

protected:
    void forwardWindowEvent(WindowEventHandler &eventHandler) override;

    void forwardMouseEvent(MouseEventHandler &eventHandler) override;

    void forwardKeyboardEvent(KeyboardEventHandler &eventHandler) override;

private:
    SDL_Event mInputEvent{};
};
