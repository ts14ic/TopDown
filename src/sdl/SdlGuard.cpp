#include "SdlGuard.h"
#include "SdlEngine.h"
#include <SDL.h>

SdlGuard::SdlGuard() {
    Uint32 initFlags = SDL_INIT_VIDEO | SDL_INIT_TIMER;
    if (0 != SDL_Init(initFlags)) {
        throw SdlEngine::FailedSdlInitException{SDL_GetError()};
    }
}

SdlGuard::~SdlGuard() {
    SDL_Quit();
}
