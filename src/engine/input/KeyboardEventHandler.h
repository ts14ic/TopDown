//
// Created by ts14ic on 15/12/17.
//

#pragma once

#include "KeyboardEvent.h"

class KeyboardEventHandler {
public:
    virtual ~KeyboardEventHandler() = 0;

    virtual void handleKeyEvent(const KeyboardEvent& event) = 0;
};
