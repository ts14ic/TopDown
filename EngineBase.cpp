//
// Created by ts14ic on 12/2/17.
//
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <iostream>
#include "EngineBase.h"
#include "sdlwrap.h"

class FailedSDLInitException : std::runtime_error {
public:
    explicit FailedSDLInitException(const char *message) : runtime_error(message) {}
};

EngineBase::EngineBase(int screenWidth, int screenHeight)
        : mScreenWidth(screenWidth), mScreenHeight(screenHeight) {
    init();
}

EngineBase::EngineBase() : EngineBase(800, 600) {}

void EngineBase::init() {
    Uint32 initFlags = SDL_INIT_VIDEO | SDL_INIT_TIMER;
    if (0 != SDL_Init(initFlags)) {
        throw FailedSDLInitException{SDL_GetError()};
    }

    mWindow.reset(SDL_CreateWindow(
            "TopDown - Reborn",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            mScreenWidth, mScreenHeight,
            SDL_WINDOW_SHOWN
    ));
    if (!mWindow) {
        throw FailedSDLInitException{SDL_GetError()};
    }

    mRenderer.reset(SDL_CreateRenderer(
            mWindow.get(), -1,
            SDL_RENDERER_ACCELERATED |
            SDL_RENDERER_PRESENTVSYNC
    ));
    if (!mRenderer) {
        throw FailedSDLInitException{SDL_GetError()};
    }

    // FIXME Renderer should not be global
    renderer() = mRenderer.get();

    int IMG_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (IMG_flags != (IMG_Init(IMG_flags) & IMG_flags)) {
        throw FailedSDLInitException{IMG_GetError()};
    }

    if (0 != Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)) {
        throw FailedSDLInitException{Mix_GetError()};
    }

    SDL_ShowCursor(SDL_DISABLE);

    SDL_SetRenderDrawColor(mRenderer.get(), 0x10, 0x10, 0x10, 0xff);
    SDL_RenderClear(mRenderer.get());
    SDL_RenderPresent(mRenderer.get());
}

EngineBase::~EngineBase() {
    SDL_Quit();
}
