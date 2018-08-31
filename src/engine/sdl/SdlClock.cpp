#include "SdlClock.h"
#include <SDL_timer.h>

unsigned long SdlClock::get_current_time() const {
    return SDL_GetTicks();
}
