//
// Created by ts14ic on 12/3/17.
//
#pragma once

union SDL_Event;

class InputContext {
public:
    virtual SDL_Event& getInputEvent() = 0;

    virtual ~InputContext() = 0;
};
