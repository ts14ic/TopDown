#include "SdlClock.h"
#include <SDL_timer.h>

unsigned long SdlClock::getCurrentTime() const {
    return SDL_GetTicks();
}
