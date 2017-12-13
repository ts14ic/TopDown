//
// Created by ts14ic on 12/13/17.
//

#include "SdlRenderContext.h"
#include "../assets/Assets.h"
#include "../assets/Texture.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

SdlRenderContext::SdlRenderContext(int screenWidth, int screenHeight)
        : mScreenWidth(screenWidth), mScreenHeight(screenHeight) {
    init();
}

void SdlRenderContext::init() {
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

SdlRenderContext::~SdlRenderContext() {
    SDL_Quit();
}

SDL_Renderer* SdlRenderContext::getRenderer() {
    return mRenderer.get();
}

int SdlRenderContext::getScreenHeight() {
    return mScreenHeight;
}

int SdlRenderContext::getScreenWidth() {
    return mScreenWidth;
}

void SdlRenderContext::render(const Texture& texture, int x, int y) {
    if(texture.isLoaded()) {
        SDL_Rect destRect = {x, y, texture.getWidth(), texture.getHeight()};
        SDL_RenderCopy(mRenderer.get(), texture.getWrapped(), nullptr, &destRect);
    }
}

void SdlRenderContext::render(Texture const& texture, int x, int y, float angle) {
    if(texture.isLoaded()) {
        SDL_Rect destRect = {x, y, texture.getWidth(), texture.getHeight()};
        SDL_RenderCopyEx(mRenderer.get(), texture.getWrapped(), nullptr, &destRect, angle, nullptr, SDL_FLIP_NONE);
    }
}

void SdlRenderContext::SDLDeleter::operator()(SDL_Window* p) {
    SDL_DestroyWindow(p);
}

void SdlRenderContext::SDLDeleter::operator()(SDL_Renderer* p) {
    SDL_DestroyRenderer(p);
}
