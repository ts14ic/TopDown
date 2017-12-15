//
// Created by ts14ic on 15/12/17.
//

#pragma once

class MouseEvent;

class MouseEventHandler {
public:
    virtual ~MouseEventHandler() = 0;

    virtual void handleMouseEvent(const MouseEvent& event) = 0;
};
