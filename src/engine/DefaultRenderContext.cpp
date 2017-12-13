//
// Created by ts14ic on 12/13/17.
//

#include "DefaultRenderContext.h"
#include "../assets/Assets.h"
#include "../texture/Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

DefaultRenderContext::DefaultRenderContext(int screenWidth, int screenHeight)
        : mScreenWidth(screenWidth), mScreenHeight(screenHeight) {
    init();
}

void DefaultRenderContext::init() {
    Uint32 initFlags = SDL_INIT_VIDEO | SDL_INIT_TIMER;
    if(0 != SDL_Init(initFlags)) {
        throw FailedSDLInitException{SDL_GetError()};
    }

    mWindow.reset(SDL_CreateWindow(
            "TopDown - Reborn",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            mScreenWidth, mScreenHeight,
            SDL_WINDOW_SHOWN
    ));
    if(!mWindow) {
        throw FailedSDLInitException{SDL_GetError()};
    }

    mRenderer.reset(SDL_CreateRenderer(
            mWindow.get(), -1,
            SDL_RENDERER_ACCELERATED |
            SDL_RENDERER_PRESENTVSYNC
    ));
    if(!mRenderer) {
        throw FailedSDLInitException{SDL_GetError()};
    }

    int IMG_flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if(IMG_flags != (IMG_Init(IMG_flags) & IMG_flags)) {
        throw FailedSDLInitException{IMG_GetError()};
    }

    if(0 != Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)) {
        throw FailedSDLInitException{Mix_GetError()};
    }

    SDL_ShowCursor(SDL_DISABLE);

    SDL_SetRenderDrawColor(mRenderer.get(), 0x10, 0x10, 0x10, 0xff);
    SDL_RenderClear(mRenderer.get());
    SDL_RenderPresent(mRenderer.get());
}

DefaultRenderContext::~DefaultRenderContext() {
    SDL_Quit();
}

SDL_Renderer* DefaultRenderContext::getRenderer() {
    return mRenderer.get();
}

int DefaultRenderContext::getScreenHeight() {
    return mScreenHeight;
}

int DefaultRenderContext::getScreenWidth() {
    return mScreenWidth;
}

void DefaultRenderContext::render(const Texture& texture, int x, int y) {
    if(texture.isLoaded()) {
        SDL_Rect destRect = {x, y, texture.getWidth(), texture.getHeight()};
        SDL_RenderCopy(mRenderer.get(), texture.getWrapped(), nullptr, &destRect);
    }
}

void DefaultRenderContext::render(Texture const& texture, int x, int y, float angle) {
    if(texture.isLoaded()) {
        SDL_Rect destRect = {x, y, texture.getWidth(), texture.getHeight()};
        SDL_RenderCopyEx(mRenderer.get(), texture.getWrapped(), nullptr, &destRect, angle, nullptr, SDL_FLIP_NONE);
    }
}

void DefaultRenderContext::SDLDeleter::operator()(SDL_Window* p) {
    SDL_DestroyWindow(p);
}

void DefaultRenderContext::SDLDeleter::operator()(SDL_Renderer* p) {
    SDL_DestroyRenderer(p);
}
