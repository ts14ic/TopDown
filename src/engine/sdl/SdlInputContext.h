//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "engine/input/InputContext.h"

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
