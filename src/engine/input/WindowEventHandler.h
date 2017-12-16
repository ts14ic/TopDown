//
// Created by ts14ic on 15/12/17.
//

#pragma once

class WindowEvent;

class WindowEventHandler {
public:
    virtual ~WindowEventHandler() = 0;

    virtual void handleWindowEvent(const WindowEvent& event) = 0;
};
