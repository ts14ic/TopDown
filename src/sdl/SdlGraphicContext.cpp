//
// Created by ts14ic on 12/13/17.
//

#include "SdlGraphicContext.h"
#include "../engine/resources/Resources.h"
#include "../shape/Box.h"
#include "../shape/Color.h"
#include "SdlTexture.h"
#include <SDL.h>

SdlGraphicContext::SdlGraphicContext(SDL_Window* window, SDL_Renderer* renderer)
        : mWindow{window}, mRenderer{renderer} {
}

void SdlGraphicContext::refreshScreen() {
    SDL_RenderPresent(mRenderer);
}

void SdlGraphicContext::clearScreen() {
    SDL_RenderClear(mRenderer);
}

void SdlGraphicContext::render(const Texture& texture, int x, int y) {
    if(texture.isLoaded()) {
        SDL_Rect destRect = {x, y, texture.getWidth(), texture.getHeight()};
        SDL_RenderCopy(mRenderer, dynamic_cast<const SdlTexture&>(texture).getWrappedTexture(), nullptr, &destRect);
    }
}

void SdlGraphicContext::render(Texture const& texture, int x, int y, float angle) {
    if(texture.isLoaded()) {
        SDL_Rect destRect = {x, y, texture.getWidth(), texture.getHeight()};
        SDL_RenderCopyEx(mRenderer, dynamic_cast<const SdlTexture&>(texture).getWrappedTexture(), nullptr,
                         &destRect,
                         angle, nullptr, SDL_FLIP_NONE);
    }
}

void SdlGraphicContext::renderBox(const Box& box, const Color& color) {
    SDL_Rect rect{
            static_cast<int>(box.getX()),
            static_cast<int>(box.getY()),
            static_cast<int>(box.getWidth()),
            static_cast<int>(box.getHeight())
    };
    SDL_SetRenderDrawColor(
            mRenderer,
            static_cast<Uint8>(color.getRed()),
            static_cast<Uint8>(color.getGreen()),
            static_cast<Uint8>(color.getBlue()),
            static_cast<Uint8>(color.getAlpha())
    );
    SDL_RenderFillRect(mRenderer, &rect);
}

int SdlGraphicContext::getScreenWidth() {
    SDL_GetWindowSize(mWindow, &mScreenWidth, &mScreenHeight);
    return mScreenWidth;
}

int SdlGraphicContext::getScreenHeight() {
    SDL_GetWindowSize(mWindow, &mScreenWidth, &mScreenHeight);
    return mScreenHeight;
}
