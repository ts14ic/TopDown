
#include <SDL_events.h>

SDL_Event& gameEvent() {
    static SDL_Event ret;
    return ret;
}
