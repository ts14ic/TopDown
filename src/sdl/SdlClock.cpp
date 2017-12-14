//
// Created by ts14ic on 12/14/17.
//

#include "SdlClock.h"
#include <SDL_timer.h>

unsigned long SdlClock::getCurrentTime() const {
    return SDL_GetTicks();
}
