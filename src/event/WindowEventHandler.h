//
// Created by ts14ic on 15/12/17.
//

#pragma once

class WindowEventHandler {
public:
    virtual ~WindowEventHandler() = 0;

    virtual void handleWindowEvent() = 0;
};
