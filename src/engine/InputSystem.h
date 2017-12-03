//
// Created by ts14ic on 12/3/17.
//
#pragma once

#include <SDL_events.h>

class InputSystem {
public:
    SDL_Event& getInputEvent();
private:
    SDL_Event mInputEvent {};
};
