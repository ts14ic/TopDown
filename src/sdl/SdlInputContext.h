//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "../engine/input//InputContext.h"
#include "../engine/input//MouseEvent.h"
#include "../engine/input//KeyboardEvent.h"
#include "../engine/input//WindowEvent.h"
#include <SDL_events.h>

class WindowEventHandler;

class MouseEventHandler;

class KeyboardEventHandler;

class EventHandler;

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
