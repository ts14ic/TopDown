//
// Created by ts14ic on 12/13/17.
//

#pragma once

#include "../engine/InputContext.h"
#include <SDL_events.h>

class SdlInputContext : public InputContext {
public:
    SDL_Event& getInputEvent() override;

private:
    SDL_Event mInputEvent{};
};
