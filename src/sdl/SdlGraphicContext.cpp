//
// Created by ts14ic on 12/13/17.
//

#include "SdlGraphicContext.h"
#include "../assets/Assets.h"
#include "../shape/Box.h"
#include "../shape/Color.h"
#include "SdlTexture.h"
#include <SDL.h>
#include <SDL_image.h>

SdlGraphicContext::SdlGraphicContext(int screenWidth, int screenHeight)
        : mScreenWidth(screenWidth), mScreenHeight(screenHeight) {
}

SDL_Renderer* SdlGraphicContext::getRenderer() {
    return mRenderer.get();
}

int SdlGraphicContext::getScreenHeight() {
    return mScreenHeight;
}

int SdlGraphicContext::getScreenWidth() {
    return mScreenWidth;
}

void SdlGraphicContext::refreshScreen() {
    SDL_RenderPresent(getRenderer());
}

void SdlGraphicContext::clearScreen() {
    SDL_RenderClear(getRenderer());
}

void SdlGraphicContext::render(const Texture& texture, int x, int y) {
    if(texture.isLoaded()) {
        SDL_Rect destRect = {x, y, texture.getWidth(), texture.getHeight()};
        SDL_RenderCopy(getRenderer(), dynamic_cast<const SdlTexture&>(texture).getWrappedTexture(), nullptr, &destRect);
    }
}

void SdlGraphicContext::render(Texture const& texture, int x, int y, float angle) {
    if(texture.isLoaded()) {
        SDL_Rect destRect = {x, y, texture.getWidth(), texture.getHeight()};
        SDL_RenderCopyEx(getRenderer(), dynamic_cast<const SdlTexture&>(texture).getWrappedTexture(), nullptr,
                         &destRect,
                         angle, nullptr, SDL_FLIP_NONE);
    }
}

void SdlGraphicContext::renderBox(const Box& box, const Color& color) {
    SDL_Rect rect{
            // todo add inferring getters for Box
            static_cast<int>(box.getX()),
            static_cast<int>(box.getY()),
            static_cast<int>(box.getWidth()),
            static_cast<int>(box.getHeight())
    };
    SDL_SetRenderDrawColor(
            getRenderer(),
            // todo add inferring getters for Color
            static_cast<Uint8>(color.getRed()),
            static_cast<Uint8>(color.getGreen()),
            static_cast<Uint8>(color.getBlue()),
            static_cast<Uint8>(color.getAlpha())
    );
    SDL_RenderFillRect(getRenderer(), &rect);
}

SdlGraphicContext::FailedToLoadTextureException::FailedToLoadTextureException(const char* message)
        : runtime_error(message) {}

SdlTexture SdlGraphicContext::loadTexture(const char* path) {
    struct SDLSurfaceDeleter {
        void operator()(SDL_Surface* surf) {
            SDL_FreeSurface(surf);
        }
    };

    std::unique_ptr<SDL_Surface, SDLSurfaceDeleter> buf{IMG_Load(path)};
    if(!buf) {
        throw FailedToLoadTextureException{IMG_GetError()};
    }

    std::unique_ptr<SDL_Texture, SdlTexture::TextureDeleter> newTex{
            SDL_CreateTextureFromSurface(getRenderer(), buf.get())
    };
    if(!newTex) {
        throw FailedToLoadTextureException{SDL_GetError()};
    }

    SdlTexture tex{std::move(newTex), buf->w, buf->h};
    SDL_Log("SdlTexture loaded: %s.\n", path);

    return tex;
}

void SdlGraphicContext::setSdlRenderer(std::unique_ptr<SDL_Window, SdlGraphicContext::SdlDeleter> sdlWindow,
                                       std::unique_ptr<SDL_Renderer, SdlGraphicContext::SdlDeleter> sdlRenderer) {
    mWindow = std::move(sdlWindow);
    mRenderer = std::move(sdlRenderer);
}

void SdlGraphicContext::SdlDeleter::operator()(SDL_Window* p) {
    SDL_DestroyWindow(p);
}

void SdlGraphicContext::SdlDeleter::operator()(SDL_Renderer* p) {
    SDL_DestroyRenderer(p);
}
