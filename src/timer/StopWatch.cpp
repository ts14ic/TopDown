#include "StopWatch.h"
#include <SDL_timer.h>

StopWatch::StopWatch()
: _startedAt{0ul}
{
}

void StopWatch::restart() {
    _startedAt = SDL_GetTicks();
}

unsigned StopWatch::getTicks() const {
    return SDL_GetTicks() - _startedAt;
}

bool StopWatch::ticksHavePassed(unsigned ticks) const {
    return getTicks() >= ticks;
}
