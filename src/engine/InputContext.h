//
// Created by ts14ic on 12/3/17.
//
#pragma once

union SDL_Event;

class InputContext {
public:
    // todo SDL_Event is too specific
    virtual SDL_Event& getInputEvent() = 0;

    virtual ~InputContext() = 0;
};
