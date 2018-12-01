#include "SdlClockEngine.h"
#include <SDL_timer.h>

std::size_t SdlClockEngine::get_current_time() const {
    return SDL_GetTicks();
}
