//
// Created by ts14ic on 12/3/17.
//
#pragma once

class WindowEventHandler;

class MouseEventHandler;

class KeyboardEventHandler;

class EventHandler;

class InputContext {
public:
    virtual ~InputContext() = 0;

    virtual void pollEvents(EventHandler &eventHandler) = 0;

protected:
    virtual void forwardWindowEvent(WindowEventHandler &eventHandler) = 0;

    virtual void forwardMouseEvent(MouseEventHandler &eventHandler) = 0;

    virtual void forwardKeyboardEvent(KeyboardEventHandler &eventHandler) = 0;
};
