#include "SdlClockEngine.h"
#include <SDL_timer.h>

unsigned long SdlClockEngine::get_current_time() const {
    return SDL_GetTicks();
}
